
'''
미국 세금을 위한 국내 주식선물 거래 차액 계산 프로그램
'''

'''
note) Error margin on 수수료, 세금합계, 순수익
    얘를 들어, a) 4 buy, b) 1 sell, c) 3 buy, d) 4 sell, e) 2 sell 
    이런거 계산하려면 
    d) 의 경우는 아래처럼 계산해야 한다.
        a) 4 buy --> 3 sell (a) 의 수수료 * 3/4 + d)의 수수료 * 3/4)
        c) 3 buy --> 1 sell (c) 의 수수료 * 1/3 + d)의 수수료 * 1/4)
        
    이렇게 되면, 수수료가 소수점이 나올 수 있고, 그래서 floor 를 쓴다. 
    그런데 쌍 floor 결과가 관련 수수료의 실 지불값보다 -1원 차이가 날 수 있다. 
    그렇게 되면 이익은 +1 원 으로 계산되는 오차가 생긴다.
    
    그런데 이걸 정확하게 하긴 너무 어렵다. 그냥 이렇게 두기로 했다.
'''

import math
import copy
import pandas as pd
from datetime import datetime
from typing import List

import util as util

TAX_YEAR = 2023

알수없는금액 = -1234567890

class Tx:
    def __init__(self):
        self.key        = None
        self.거래일자   = None
        self.거래종류   = None
        self.종목번호   = None
        self.종목명     = None
        self.수량       = None
        self.단가       = None
        self.수수료     = None
        self.예수금전잔 = None
        self.예수금금잔 = None
        self.정산금액   = None
        self.약정금액   = None

    def setWithSeries(self, row: pd.Series):
        
        self.key = row['key']
        self.거래일자: datetime = row['거래일자']
        self.거래종류 = row['거래종류'] # 입금, 출금, 매도, 매수. ('매도' 는 매도 진입 또는 매도 청산 둘중 하나임)
        self.종목번호 = row['종목번호']
        self.종목명 = row['종목명']
        self.수량   = row['수량']
        self.단가   = row['단가']
        self.수수료 = row['수수료']
        
        # 정산금액이 일일정산일때는 '거래종류'가 입금이면 +, 출금이면 - 이다.
        # 정산금액이 진입이나 청산일때는 적요명이 '출금'으로 끝나면 -, '입금'으로 끝나면 + 인데
        # 이걸 좀 더 편하게 하려면 차라리 
        # '예수금금잔' (오늘잔액인듯) - '예수금전잔' (어제잔액인듯) 을 해보는게 낫다. + 이면 이익, - 이면 손실
        self.예수금전잔 = row['예수금전잔']
        self.예수금금잔 = row['예수금금잔']
        정산금액 = row['정산금액']
        assert abs(정산금액) == abs(self.예수금금잔 - self.예수금전잔)
        
        self.정산금액 = self.예수금금잔 - self.예수금전잔 # 손해면 음수, 이익이면 양수
        self.약정금액 = row['약정금액']

# 매수 청산, 매도 청산
class 청산Tx (Tx):
    def __init__(self):
        super().__init__()
        
    def initWithSeries(self, row: pd.Series):
        super().setWithSeries(row)

        self.남은수량 = self.수량
        
    def adjust수량(self, new수량: int):
        '''
        initWith청산Tx() 참조.
        진입과 청산 resultTx를 만들다 보면, 진입txList 가 0개인데 청산이 남은수량이 아직 있는 경우도 있다.
        이 경우 청산tx의 남은수량을 가지고 진입tx를 생성한다.
        그리고 청산tx의 내부 값들도 실제 청산 수량 = 원래tx의 수량 - 남은수량 에 맞춰 바꿔준다.
        '''
        assert new수량 < self.수량
        수량ratio = new수량 / self.수량
       
        # 금잔 = 전잔 + 이익 - 수수료        
        청산이속한원본tx의총이익 = self.예수금금잔 - self.예수금전잔 + self.수수료
        
        print("=======>", new수량, 수량ratio)
        self.예수금금잔 = self.예수금전잔 + 청산이속한원본tx의총이익 * 수량ratio - self.수수료 * 수량ratio
        
        self.수수료 = self.수수료 * 수량ratio
        self.정산금액 = self.정산금액 * 수량ratio
        self.약정금액 = self.약정금액 * 수량ratio           
        
        self.수량 = new수량
        self.남은수량 = 0

# 미래의 청산. 이것은 TaxYear < 청산일자 인 경우를 위한 것이다.
# 진입일자 <= taxYear 라면 청산되지 않았어도 일일정산이 발생하여 profit이 생긴다.
class 미실현청산Tx (청산Tx):
    def __init__(self):
        super().__init__()
        self.key = -1
        pass

# 매수 진입, 매도 진입
class 진입Tx (Tx):
    def __init__(self):
        super().__init__()
        
    def initWithSeries(self, row: pd.Series):
        super().setWithSeries(row)
        self.남은수량 = self.수량
        
    def initWith청산Tx(self, 청산tx: 청산Tx):
        '''
        청산Tx의 남은수량으로 집입Tx를 초기화한다.
        '''
        self.수량       = 청산tx.남은수량
        self.남은수량    = 청산tx.남은수량   

        진입수량ratio = 청산tx.남은수량 / 청산tx.수량
        self.수수료     = 청산tx.수수료 * 진입수량ratio
        
        '''
        청산이 일어난 후 청산만 고려한 금잔이 이 진입Tx의 전잔이 된다.
        청산만 고려한 금잔 = 청산tx전잔 + (청산수량에 대한) 이익 - (청산수량에 대한) 수수료
        여기서... 원래 tx에 100개 거리인데 30개 청산했다면, 70개가 진입이 되는 셈이다.
        '''
        청산이속한원본tx의총이익 = 청산tx.예수금금잔 - 청산tx.예수금전잔 + 청산tx.수수료
        청산수량ratio = (청산tx.수량 - 청산tx.남은수량) / 청산tx.수량
       
        보정된청산tx의_예수금금잔 = 청산tx.예수금전잔 + 청산이속한원본tx의총이익 * 청산수량ratio - 청산tx.수수료 * 청산수량ratio
        self.예수금전잔 = 보정된청산tx의_예수금금잔
        self.예수금금잔 = 청산tx.예수금금잔
        
        self.정산금액   = 청산tx.정산금액 * 진입수량ratio
        self.약정금액   = 청산tx.약정금액 * 진입수량ratio
        
        self.key        = 청산tx.key
        self.거래일자   = 청산tx.거래일자
        self.거래종류   = 청산tx.거래종류
        self.종목번호   = 청산tx.종목번호
        self.종목명     = 청산tx.종목명
        self.단가       = 청산tx.단가


class ResultTx:
    def __init__(self, 진입tx: 진입Tx, 청산tx: 청산Tx, 거래수량: int):
        
        self.진입tx = 진입tx
        self.청산tx = 청산tx
        
        청산이_발생 = not isinstance(청산tx, 미실현청산Tx)
        
        if 청산이_발생:
            assert 진입tx.거래일자 <= 청산tx.거래일자
            assert 진입tx.종목명 == 청산tx.종목명

        self.거래수량 = 거래수량
        assert 거래수량 <= 진입tx.수량
        
        if 청산이_발생:
            assert 거래수량 <= 청산tx.수량

        진입수량Ratio = 거래수량 / 진입tx.수량
        청산수량Ratio = 거래수량 / 청산tx.수량 if 청산이_발생 else 0

        진입총수수료 = math.floor(진입tx.수수료 * 진입수량Ratio)
        청산총수수료 = math.floor(청산tx.수수료 * 청산수량Ratio) if 청산이_발생 else 0
        self.총수수료 = 진입총수수료 + 청산총수수료
        self.총세금합계 = 0
        
        # 순수익은 나중에 계산해서 채운다
        self.순수익 = None  
        
    def getTaxReportRow(self):
    
        # self.진입tx.거래일자 를 string으로 바꾼다. "03/31/2023" 의 형식으로.
        dateFormat = "%m/%d/%Y"
        진입일자 = self.진입tx.거래일자.strftime(dateFormat)
        
        청산일자 = ""
        if isinstance(self.청산tx, 미실현청산Tx): 
            청산일자 = "not yet"
        else:
            청산일자 = self.청산tx.거래일자.strftime(dateFormat)

        return [self.진입tx.종목명, 
                진입일자, self.진입tx.단가,
                청산일자, self.청산tx.단가 if not isinstance(self.청산tx, 미실현청산Tx) else f"{알수없는금액}",
                self.거래수량, 
                int(self.총수수료), 
                int(self.총세금합계), 
                int(round(self.순수익))]


def update_profit(종목번호df: pd.DataFrame, taxYear: int, 진입청산txList: List[ResultTx]):
    '''
    청산일자는 year 가 넘어가도 된다.
    그러나 일일정산중 year 가 넘어가는 항목은 계산에 포함하지 않는다.
    year가 넘어가는 항목 중, 일일정산이 1건이라도 있으면 결과에 포함해야 함. 아니면 결과에서 제거한다.
    '''

# # 청산Tx가 사실은 미실현청산Tx 라면 "미래"를 프린트한다.
# if isinstance(tx, 미실현청산Tx):

    for resultTx in 진입청산txList:
        
        startCalc = False
        거래수량 = -1
        for index, row in 종목번호df.iterrows():
            
            # 일일정산
            if startCalc and (row['거래종류'] != '매수' and row['거래종류'] != '매도'):
                assert row['key'] != resultTx.진입tx.key
                assert row['key'] != ""
                
                # 날짜가 taxYear 안에 있어야 한다.
                if row['거래일자'].year != taxYear:
                    continue
                
                예수금금잔 = row['예수금금잔']
                예수금전잔 = row['예수금전잔']
                수수료 = row['수수료']
                수량 = row['수량']
                
                개당수익 = ( 예수금금잔 - 예수금전잔 + 수수료 ) / 수량
                resultTx.순수익 = resultTx.순수익 + (개당수익 * resultTx.거래수량)
            
            if row['key'] == resultTx.진입tx.key:
                assert startCalc == False
                startCalc = True
                
                assert resultTx.순수익 == None
                
                # 예수금 금잔 == 예수금전잔 + 수익 - 수수료
                진입tx = resultTx.진입tx
                개당수익 = ( 진입tx.예수금금잔 - 진입tx.예수금전잔 + 진입tx.수수료 ) / 진입tx.수량
                resultTx.순수익 = 개당수익 * resultTx.거래수량
                
            elif row['key'] == resultTx.청산tx.key:
                assert startCalc == True
                startCalc = False
                
                assert resultTx.순수익 != None
                청산tx = resultTx.청산tx
                개당수익 = (청산tx.예수금금잔 - 청산tx.예수금전잔 + 청산tx.수수료) / 청산tx.수량
                resultTx.순수익 = resultTx.순수익 + 개당수익 * resultTx.거래수량
                
                break


def generate_종목번호_진입청산목록_sub(종목번호: str, 종목번호df: pd.DataFrame, idx, taxYear: int, 보정된진입tx: 진입Tx, resultTxList: List[ResultTx]):
    '''
    종목 foo가 원본 df의 index 0, 10, 30, 33 에 존재했다면
    foo를 위한 종목번호df 의 4개의 데이터의 index (key) 는 0, 10, 30, 33이 된다.
    그래서.. 이 함수가 호출될 때, 예를 들어, 이전에 30번째 idx 까지 마치면, 31을 idx로 넘겨주게 된다.
    그런데 31번째 항목이 원본 df에서 다른 종목이므로...
    foo를 위한 종목번호df에서 31번을 바로 access하면 에러가 나게 된다.
    따라서 31번 이후의 데이터를 다시 뽑아 종목번호df를 생성한다.
    '''
    if idx > 종목번호df['key'].max():
        return
    
    print(f"generate_종목번호_진입청산목록_sub: ",
          " idx: ", idx,
          " 보정된진입tx? :", True if 보정된진입tx != None else False
            )
    
    종목번호df = 종목번호df[(종목번호df.index >= idx) & (종목번호df['종목번호'] == 종목번호)]
    
    종목명 = 종목번호df.iloc[0]['종목명']    # 디버깅용

    진입Df = None
    청산Df = None

    idx = 종목번호df.iloc[0]['key']
    
    if 종목번호df.loc[idx, '거래종류'] == '매수':
        # key idx 부터, '거래종류'가 '매수'인 것들을 진입df 로 만든다.
        진입Df = 종목번호df[(종목번호df.index >= idx) & (종목번호df['거래종류'] == '매수')]
        청산Df = 종목번호df[(종목번호df.index >= idx) & (종목번호df['거래종류'] == '매도')]
    elif 종목번호df.loc[idx, '거래종류'] == '매도':
        # key idx 부터, '거래종류'가 '매도'인 것들을 진입df 로 만든다.
        진입Df = 종목번호df[(종목번호df.index >= idx) & (종목번호df['거래종류'] == '매도')]
        청산Df = 종목번호df[(종목번호df.index >= idx) & (종목번호df['거래종류'] == '매수')]
    else:
        print("진입df/청산df 만들떄: unexpected first tx: ", 종목번호df.iloc[0]['거래종류'])
        exit(1)

    # 110.py를 이렇게 만들어서 여기서도 이렇게 그냥 했음
    진입txList: List[진입Tx] = []
    for index, 진입Row in 진입Df.iterrows():
        진입tx = 진입Tx()
        진입tx.initWithSeries(진입Row)
        
        # 진입tx.거래일자 <= taxYear 이어야 한다.
        if 진입tx.거래일자.year <= TAX_YEAR:
            진입txList.append(진입tx)
            
    # 보정된진입tx 가 있다면, 진입txList[0]로 대체한다.
    if 보정된진입tx != None:
        진입txList[0] = 보정된진입tx

    청산tx = None
    새로운종목df로시작해라 = False
    보정된진입tx를사용하는새로운종목df로시작해라 = False
    보정된진입tx = None

    for index, 청산Row in 청산Df.iterrows():
        
        청산tx = 청산Tx()
        청산tx.initWithSeries(청산Row)
    
        assert taxYear <= 청산tx.거래일자.year and 청산tx.거래일자.year <= taxYear + 1       
        assert len(진입txList) > 0

        for 진입tx in 진입txList:
            
            if 진입tx.남은수량 <= 청산tx.남은수량:
                resultTxList.append(ResultTx(진입tx, 청산tx, 진입tx.남은수량))
                청산tx.남은수량 -= 진입tx.남은수량
                진입tx.남은수량 = 0
                
                print("\tcase 1)", 진입tx.수량, 진입tx.남은수량, "/", 청산tx.수량, 청산tx.남은수량)
                
            else:   # 진입tx.남은수량 > 청산tx.남은수량:
                resultTxList.append(ResultTx(진입tx, 청산tx, 청산tx.남은수량))
                진입tx.남은수량 -= 청산tx.남은수량
                청산tx.남은수량 = 0

                print("\tcase 2)", 진입tx.수량, 진입tx.남은수량, "/", 청산tx.수량, 청산tx.남은수량)

            if 청산tx.남은수량 == 0 and 진입tx.남은수량 == 0:
                print("\t진입tx, 청산tx 모두 처리 완료")
                새로운종목df로시작해라 = True
                break
                
            if 청산tx.남은수량 == 0 and 진입tx.남은수량 > 0:
                print("\t청산tx 하나 처리 완료")
                break

        if 새로운종목df로시작해라 == True:
            break
        
        # remove any 진입tx from 진입List if 진입tx.수량 == 0
        진입txList = [진입tx for 진입tx in 진입txList if 진입tx.남은수량 > 0 and 진입tx.key <= 청산tx.key]
        
        print("len(진입txList)" , len(진입txList))
        
        '''
        진입txList 가 0개인데 청산이 남은수량이 아직 있는 경우도 있다.
        이 경우는 남은 청산을 진입으로 처리해야 할 거 같다.
        예를 들어, 아래같은 구성도 있다.
            매수2 매도3 매수 1
        매수진입 2, 매도창산 2, 매도진입 1, 매수청산 1로 처리하도록 하자.
        '''
        if len(진입txList) == 0 and 청산tx.남은수량 > 0:
            '''
            여기서... 원래 tx에 100개 거래인데 진입을 다 소진하고도 청산tx.남은수량 == 70 이라면
            청산tx는 100개 수량이 아니고 70개 수량으로 바꾸고, 수수료, 이익 등도 비 비율로 바꿔야 한다.
            '''
            보정된진입tx = 진입Tx()
            보정된진입tx.initWith청산Tx(청산tx)
            
            print("청산tx.수량 보정: to ", 청산tx.수량 - 청산tx.남은수량)            
            청산tx.adjust수량(청산tx.수량 - 청산tx.남은수량)       

            print ("===> 청산 전잔/금잔/차액,", 청산tx.예수금전잔,",", 청산tx.예수금금잔, ",",청산tx.예수금금잔 - 청산tx.예수금전잔)
            print ("===> 진입 전잔/금잔/차액,", 보정된진입tx.예수금전잔, ",",보정된진입tx.예수금금잔, ",",보정된진입tx.예수금금잔 - 보정된진입tx.예수금전잔)
            
            보정된진입tx를사용하는새로운종목df로시작해라 = True
            break
    
    '''
    여기에 오는 경우는 
    1) 진입tx와 매칭되는 청산tx를 일단 다 찾은 경우이다. 
        a) 그런데 뒤에 또 진입/청산이 존재하거나 
        b) 아니면 종목번호df의 끝에 도달한 경우이다.
    2) 또는 청산tx가 처음부터 아예 없거나...
    3) 또는 진입tx가 더 남아 있는데 청산tx는 다 소진했거나 (내년도 만기 선물)
    4) 또는 이런 케이스
        - 매수 10, 매도 15, 매수 5 인 경우, 앞의 매수진입 10과 매도청산 10으로 resultTx를 만들고
        - 이 함수를 다시 호출하면서 매도진입 5 를 첫번쨰 진입tx로 사용해야 한다.
    '''
    
    # 1-a)
    if 새로운종목df로시작해라 == True:
        print(f"\t종목 {종목명} - sub 종목테이블 시작할께요. index from {청산tx.key + 1}")
        generate_종목번호_진입청산목록_sub(종목번호, 종목번호df, 청산tx.key + 1, taxYear, None, resultTxList)
        return
    
    # 4) 의 경우
    if 보정된진입tx를사용하는새로운종목df로시작해라 == True:
        print(f"\t종목 {종목명} - 보정된 진입tx로 sub 종목테이블 시작할께요. index from {청산tx.key}")
        generate_종목번호_진입청산목록_sub(종목번호, 종목번호df, 청산tx.key, taxYear, 보정된진입tx, resultTxList)
        return

    # 1-b) 의 경우
    if 청산tx != None and 청산tx.key == 청산Df.iloc[-1]['key']:
        print(f"\t종목 {종목명} 처리 완료")
        return

    # 2), 3)의 경우    
    print(f"\t종목 {종목명} - 청산없는 진입건들 {len(진입txList)}개 처리할께요")
    for 진입tx in 진입txList:
        resultTxList.append(ResultTx(진입tx, 미실현청산Tx(), 진입tx.남은수량))
    return


'''
청산 year가 다음해여도 일일정산이 12월에 존재하면 year에 존재하는 손익으로 ResultTx를 만들어야 하므로
진입 year만 부합하면 일단 목록에는 넣는다.
'''
def generate_종목번호_진입청산목록(종목번호: str, 종목번호df: pd.DataFrame, taxYear: int, resultTxList: List[ResultTx]):

    # 원래코드는 이 columns로 진입df, 청산df를 만들었는데, 일단 백업으로 그냥 둠. 나중에 지울 것    
    # columns = ['거래일자', '거래종류', '종목번호', '종목명', '수량', '단가', '수수료', 
    #            '예수금전잔', '예수금금잔', '정산금액', '약정금액', 'key']
    
    idx = 종목번호df['key'].min()
    # idx = 종목번호df.iloc[0]['key']
    # idx = 종목번호df.index[0]
    
    return generate_종목번호_진입청산목록_sub(종목번호, 종목번호df, idx, taxYear, None, resultTxList)


def saveAs(resultTxList: List[ResultTx], output_csv_path: str):
    
    columns = ['종목명', 
               '진입일자', '진입단가', 
               '청산일자', '청산단가', 
               '거래수량', '총수수료', '총세금합계', '순수익']
    dtype = {'종목명': str,
            '진입일자': str, '진입단가': float,
            '청산일자': str, '청산단가': float,
            '거래수량': int, '총수수료': float, '총세금합계': float, '순수익': float}

    assert len(columns) == len(dtype)
    
    resultDf = pd.DataFrame(columns=columns)
    # iterate dtype and convert each column to the specified type
    for column, type in dtype.items():
        resultDf[column] = resultDf[column].astype(type)
    
    for resultTx in resultTxList:
        row = resultTx.getTaxReportRow()
        
        # resultDf에 추가한다.
        resultDf.loc[len(resultDf)] = row
    
   
    # utf-8 bom 형식으로 저장해야 엑셀에서 한글이 깨지지 않는다.
    encoding = 'utf-8-sig'
    resultDf.to_csv(output_csv_path, encoding=encoding, index=False, header=True)
    

def generate_tax_file(input_csv_path: str, output_csv_path: str, taxYear: int):
    
    # input_csv_path 을 읽어서 DataFrame 으로 만든다. DataFram의 모든 값은 string 으로 인식하도록 한다.
    # excel 에서 export된 csv 는 utf-8-sig 형태이다.
    encoding = util.findEncoding(input_csv_path)
    
    # 컬럼의 타입은 모두 스트링으로 한다.
    df = pd.read_csv(input_csv_path, encoding=encoding, dtype=str)
    
    df['key'] = range(0, len(df)) # 0 부터 시작하는 key를 만든다.
    df.index = range(0, len(df)) # 0 부터 시작하는 index를 만든다. TODO 이 프로그램에서 key와 index를 혼용해서 쓰고 있다. index로 통일할 것
    
    date컬럼들 = ['거래일자']
    dateFormat = '%Y-%m-%d'
    int컬럼들 = ['수량']
    float컬럼들 = ['단가', '거래금액', '수수료', '예수금전잔', '예수금금잔', 
                '정산금액', '약정금액', '세금합계']  # 미국달러선물의 경우 단가가 1302.30
    
    ColumnDtype = util.ColumnDtype(date컬럼들, dateFormat, int컬럼들, float컬럼들)

    df = util.changeColumnDtype(df, ColumnDtype)
    
    # df['종목번호'] 들의 unique 한 값들을 리스트로 만든다.
    종목번호들 = df['종목번호'].unique().tolist()
    
    resultTxList: list[ResultTx] = []
    
    for 종목번호 in 종목번호들:
        진입청산txList = []
        
        종목번호df = df[df['종목번호'] == 종목번호]
        generate_종목번호_진입청산목록(종목번호, 종목번호df, taxYear, 진입청산txList)
        
        update_profit(종목번호df, taxYear, 진입청산txList)
        
        resultTxList.extend(진입청산txList)

    saveAs(resultTxList, output_csv_path)

      
if __name__ == "__main__":
    
    print("가끔은 입력 csv 뒤쪽에 .................. 식으로 빈 행이 있을 때가 있다. 이건 수작업으로 지울 것")
    print("종목번호가 있는 행들만 골라서 입력 화일로 만들어야 함.")
    
    input = '/mnt/c/temp/test/210전체_종목명없는것제거.csv'
    output = '/mnt/c/temp/test/210전체_종목명없는것제거_프로세싱완료.csv'
    
    # input = '/mnt/c/Users/labsu/Documents/tax/2023 (24년에 보고)/하나증권_거래내역_28767677-210-한국 주식선물 계좌.csv'
    # output = '/mnt/c/Users/labsu/Documents/tax/2023 (24년에 보고)/하나증권_거래내역_28767677-210-한국 주식선물 계좌_TAX보고형태.csv'
    result = generate_tax_file(input, output, TAX_YEAR)
    print(f'output: {result}')
    
    print(f"단가에 {알수없는금액} 이 있는 것은 미실현청산Tx을 의미하며 수작업으로 '?' 등으로 바꿀 것.")
    
    print()

