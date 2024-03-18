'''
미국 세금을 위한 국내 주식선물 거래 차액 계산 프로그램
'''

'''
Note) data file

1. 하나증권 거래 내역 (HTS의 [0711] 메뉴)을 한줄보기 클릭 후 엑셀로 저장한 후, 이를 csv로 변환하여 이 프로그램에 입력한다.
엑셀은 csv로 저장할 때 UTF8 BOM 으로 저장하고 이 인코딩은 read_csv 할 때 encoding='utf-8-sig' 로 읽어야 한다.
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
import pandas as pd
import chardet
from datetime import datetime

TAX_YEAR = 2023

class Tx:
    def __init__(self, row: pd.Series):
        self.거래일자: datetime = datetime.strptime(row['거래일자'], "%Y-%m-%d") 
        self.거래종류 = row['거래종류'] # 입금, 출금, 매도, 매수. ('매도' 는 매도 진입 또는 매도 청산 둘중 하나임)
        self.종목번호 = row['종목번호']
        self.종목명 = row['종목명']
        self.수량 = int(row['수량'].replace(',', ''))
        self.단가 = int(row['단가'].replace(',', ''))
        self.수수료 = int(row['수수료'].replace(',', ''))
        
        # 정산금액이 일일정산일때는 '거래종류'가 입금이면 +, 출금이면 - 이다.
        # 정산금액이 진입이나 청산일때는 적요명이 '출금'으로 끝나면 -, '입금'으로 끝나면 + 인데
        # 이걸 좀 더 편하게 하려면 차라리 
        # '예수금금잔' (오늘잔액인듯) - '예수금전잔' (어제잔액인듯) 을 해보는게 낫다. + 이면 이익, - 이면 손실
        self.예수금전잔 = int(row['예수금전잔'].replace(',', '')) 
        self.예수금금잔 = int(row['예수금금잔'].replace(',', '')) 
        정산금액 = int(row['정산금액'].replace(',', ''))
        assert abs(정산금액) == abs(self.예수금금잔 - self.예수금전잔)
        
        self.정산금액 = self.예수금금잔 - self.예수금전잔 # 손해면 음수, 이익이면 양수
        self.약정금액 = int(row['약정금액'].replace(',', ''))
        
        # 세금은 1년동안 2만원 수준으로 무시하자 (예탁이용료에 세금이 붙음)

# 매수 청산, 매도 청산
class 청산Tx (Tx):
    def __init__(self, row: pd.Series):
        super().__init__(row)
        self.남은수량 = self.수량

# 매수 진입, 매도 진입
class 진입Tx (Tx):
    def __init__(self, row: pd.Series):
        super().__init__(row)
        self.남은수량 = self.수량

class 일일정산Tx (Tx):
    def __init__(self, row: pd.Series):
        super().__init__(row)

# 특정 종목코드의 하루 거래내역
class Day:
    def __init__(self, date_str: str):
        
        date = datetime.strptime(date_str, "%Y-%m-%d")
        self.date = date.date()
        
        self.진입 = None
        self.청산 = None
        self.일일정산 = None        
        
    def add_진입(self, 진입: 진입Tx):
        self.진입 = 진입
        
    def add_청산(self, 청산: 청산Tx):
        self.청산 = 청산
        
    def add_일일정산(self, 일일정산: 일일정산Tx):
        self.일일정산 = 일일정산
        

def findEncoding(file_path: str) -> str:
    '''
    파일의 인코딩을 찾아 리턴한다.
    '''
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    return result['encoding']


def calculate(input_csv_path: str, output_csv_path: str, year: int):
    
    # input_csv_path 을 읽어서 DataFrame 으로 만든다. DataFram의 모든 값은 string 으로 인식하도록 한다.
    # excel 에서 export된 csv 는 utf-8-sig 형태이다.
    encoding = findEncoding(input_csv_path)
    df = pd.read_csv(input_csv_path, encoding=encoding, dtype=str)

    # df 의 모든 값들을 strip() 하기
    df = df.applymap(lambda x: x.strip() if isinstance(x, str) else x)
    
    # df['종목번호'] 들의 unique 한 값들을 리스트로 만든다.
    종목번호들 = df['종목번호'].unique().tolist()
    
    resultTxList = []
    
    for 종목번호 in 종목번호들:
        종목번호df = df[df['종목번호'] == 종목번호]
        종목resultTxList = extract_종목번호_진입청산(종목번호df)
        
        calculate_종목번호_profit(종목번호df, 종목resultTxList)
        
        resultTxList.extend(종목resultTxList)
        
    # write resultTxList to csv. make first line as header
    resultDf = pd.DataFrame([resultTx.__dict__ for resultTx in resultTxList])
    
    resultDf = resultDf[resultDf['청산거래일자'].str.startswith(str(year))]
    
    setResultDType(resultDf)

    # utf-8 bom 형식으로 저장해야 엑셀에서 한글이 깨지지 않는다.
    encoding = 'utf-8-sig'
    resultDf.to_csv(output_csv_path, encoding=encoding, index=False, header=True)


class ResultTx:
    def __init__(self, 진입tx: 진입Tx, 청산tx: 청산Tx, 거래수량: int):
        
        assert 진입tx.거래일자 <= 청산tx.거래일자
        self.진입일자: datetime = 진입tx.거래일자
        self.청산일자: datetime = 청산tx.거래일자
        
        assert 진입tx.종목명 == 청산tx.종목명
        self.종목명 = 진입tx.종목명 
        self.청산수량 = 거래수량
        self.진입단가 = 진입tx.단가
        self.청산단가 = 청산tx.단가

        assert 거래수량 <= 진입tx.수량
        assert 거래수량 <= 청산tx.수량

        진입수량Ratio = 거래수량 / 진입tx.수량
        청산수량Ratio = 거래수량 / 청산tx.수량

        self.총수수료: int = int(math.floor(진입Tx.수수료 * 진입수량Ratio) + math.floor(청산Tx.수수료 * 청산수량Ratio))
        self.총세금합계 = 0
        self.순수익 = None


def calculate_종목번호_profit(종목번호df: pd.DataFrame, 종목resultTxList: list, year: int):
    '''
    청산건에 대해 세금자료로 쓰일 값들을 뽑는다.
    진입일자, 청산일자, 종목명, 수량, 진입단가, 청산단가, 총수수료, 총세금합계, 순수익
    종목번호df를 참조하여 종목resultTxList 내의 resultTx들을 갱신한다.
    year 가 넘어가는 항목은 계산에 포함하지 않는다.
    
    TODO: 진입건에 대한 항목을 어떻게 df에서 찾나? unique id가 없음
          df 를 만들고 resultTx를 최초 만들 때 unique id를 부여하고, 그걸로 찾는게 좋을듯
    '''

    '''
    TODO
    '''
    
    pass



# year가 다음해여도 일일정산이 12월에 존재하면 year에 존재하는 손익으로 ResultTx를 만들어야 한다.    
#
# 매수진입후 매도청산하고, 그 후 매도진입하고 매수청산하는 식은 일단 고려하지 말자. 생기면 나중에 하자...
# 진입종류는 1가지, 청산도 1가지라고 가정하다.        
def extract_종목번호_진입청산(종목번호df: pd.DataFrame):

    columns = ['거래일자', '거래종류', '종목번호', '종목명', '수량', '단가', '수수료', 
               '예수금전잔', '예수금금잔', '정산금액', '약정금액']
    
    진입Df = None
    청산Df = None
    if 종목번호df.iloc[0]['거래종류'] == '매수':
        진입Df = 종목번호df[종목번호df['거래종류'].isin(['매수'])][columns]
        청산Df = 종목번호df[종목번호df['거래종류'].isin(['매도'])][columns]
    elif 종목번호df.iloc[0]['거래종류'] == '매도':
        진입Df = 종목번호df[종목번호df['거래종류'].isin(['매도'])][columns]
        청산Df = 종목번호df[종목번호df['거래종류'].isin(['매수'])][columns]
    else:
        print("unexpected first tx: ", 종목번호df.iloc[0]['거래종류'])
        exit(1)

    진입txList = []
    for index, 진입Row in 진입Df.iterrows():
        진입Tx = 진입Tx(진입Row)
        진입txList.append(진입Tx)
        
    resultTxList = []

    for index, 청산Row in 청산Df.iterrows():
        Done청산TxRow = False
        
        청산tx = 청산Tx(청산Row)
        print(청산tx)
        
        for 진입tx in 진입txList:
            print(진입tx)
            
            if 진입tx.남은수량 <= 청산tx.남은수량:
                resultTxList.append(ResultTx(진입tx, 청산tx, 진입tx.남은수량))
                청산tx.남은수량 -= 진입tx.남은수량
                진입tx.남은수량 = 0
                
                print("\tcase 1)", 청산tx.수량, 진입tx.수량)
                
                if 청산tx.남은수량 == 0:
                    Done청산Row = True
                
            else:   # 진입tx.남은수량 > 청산tx.남은수량:
                resultTxList.append(ResultTx(진입tx, 청산tx, 청산tx.남은수량))
                진입tx.남은수량 -= 청산tx.남은수량
                Done청산Row = True

                print("\tcase 1)", 청산tx.수량, 진입tx.수량)
                
            if Done청산Row:
                break
        
        # remove any 진입tx from 진입List if 진입tx.수량 == 0
        진입txList = [진입tx for 진입tx in 진입txList if 진입tx.남은수량 > 0]
        
        # print each items in 진입List
        print("진입List, len=", len(진입txList))
        for 진입tx in 진입txList:
            print("\t", 진입tx)
            
        print()
    
    assert len(진입txList) == 0
        
    return resultTxList


if __name__ == "__main__":
    input = '/mnt/c/Users/labsu/Documents/tax/2023 (24년에 보고)/하나증권_거래내역_28767677-110_위탁계좌.csv'
    output = '/mnt/c/Users/labsu/Documents/tax/2023 (24년에 보고)/하나증권_거래내역_28767677-110_TAX보고형태.csv'
    result = calculate(input, output, 
                       TAX_YEAR)
    print(f'output: {result}')
    
    print()
    print('적요명 컬럼의 [배당금]이 있는지 확인하고 수작업으로 보고하는것을 잊지 마시라')




