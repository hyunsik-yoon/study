'''
Note) data file

1. 하나증권 거래 내역 (HTS의 [0711] 메뉴)을 한줄보기 클릭 후 엑셀로 저장한 후, 이를 csv로 변환하여 이 프로그램에 입력한다.
엑셀은 csv로 저장할 때 UTF8 BOM 으로 저장하고 이 인코딩은 read_csv 할 때 encoding='utf-8-sig' 로 읽어야 한다.

2. 적요명에 '매수' '매도' 외에도 다른 필드들이 있다.
- '배당금': 1년에 몇건 안됨. 수작업으로 할 것!!
- '배당주'?? : 21년에 1건
- '예탁금이용료': 몇건 안됨. 넣는게 맞는지 잘 모르겠다. 수수료인줄 알았는데 아님. 수입이 아니고 얼마 안되니 빼자.
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

TAX_YEAR = 2023

class Tx:
    def __init__(self, row: pd.Series):
        self.거래일자 = row['거래일자']
        self.거래구분 = row['거래구분']
        self.종목코드 = row['종목코드']
        self.종목명 = row['종목명']
        self.수량 = int(row['수량'].replace(',', ''))
        self.단가 = float(row['단가'].replace(',', '')) 
        self.수수료 = int(row['수수료'].replace(',', ''))
        self.세금합계 = int(row['세금합계'].replace(',', ''))
    
class SellTx (Tx):
    def __init__(self, row: pd.Series):
        super().__init__(row)
        self.남은수량 = self.수량

    def __repr__(self):
        return f'[매도] {self.거래일자}, {self.종목명}, {self.수량} 개, {self.단가} 원/개, 수수료:{self.수수료}, 세금:{self.세금합계}'

class BuyTx (Tx):
    def __init__(self, row: pd.Series):
        super().__init__(row)
        self.남은수량 = self.수량

    def __repr__(self):
        return f'[매수] {self.거래일자}, {self.종목명}, {self.수량} 개, {self.단가} 원/개, 수수료:{self.수수료}, 세금:{self.세금합계}'

        
class 배당금:
    def __init__(self, row: pd.Series):
        self.거래일자 = row['거래일자']
        self.적요명 = row['적요명']
        self.종목코드 = row['종목코드']
        self.종목명 = row['종목명']
        self.세전금액 = int(row['거래금액'].replace(',', ''))
        self.세금합계 = int(row['세금합계'].replace(',', ''))

class ResultTx:
    def __init__(self, buyTx: BuyTx, sellTx: SellTx, 거래수량: int):
        
        self.매수거래일자: str = buyTx.거래일자
        self.매도거래일자: str = sellTx.거래일자
        
        assert buyTx.종목명 == sellTx.종목명
        assert buyTx.종목코드 == sellTx.종목코드
        self.종목명: str = sellTx.종목명
        
        self.거래수량: int = 거래수량
        
        assert 거래수량 <= buyTx.수량
        assert 거래수량 <= sellTx.수량
        
        buyRatio = 거래수량 / buyTx.수량
        sellRatio = 거래수량 / sellTx.수량
        
        self.총수수료: int = int(math.floor(buyTx.수수료 * buyRatio) + math.floor(sellTx.수수료 * sellRatio))
        self.총세금합계: int = int(math.floor(buyTx.세금합계 * buyRatio) + math.floor(sellTx.세금합계 * sellRatio))
        
        self.매수단가: int = int(buyTx.단가)
        self.매도단가: int = int(sellTx.단가)
        
        self.매수거래금액: int = int(거래수량 * buyTx.단가)
        self.매도거래금액: int = int(거래수량 * sellTx.단가)
        
        self.순수익: int = int(self.매도거래금액 - self.매수거래금액 - self.총수수료 - self.총세금합계)

def findEncoding(file_path: str) -> str:
    '''
    파일의 인코딩을 찾아 리턴한다.
    '''
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    return result['encoding']

def setResultDType(resultDf: pd.DataFrame):
    '''
    ResultTx 에서 만들어진 resultDf 의 컬럼 타입을 변경한다.
    '''
    resultDf['거래수량'] = resultDf['거래수량'].astype(int)
    resultDf['총수수료'] = resultDf['총수수료'].astype(int)
    resultDf['총세금합계'] = resultDf['총세금합계'].astype(int)
    resultDf['매수단가'] = resultDf['매수단가'].astype(int)
    resultDf['매도단가'] = resultDf['매도단가'].astype(int)
    resultDf['매수거래금액'] = resultDf['매수거래금액'].astype(int)
    resultDf['매도거래금액'] = resultDf['매도거래금액'].astype(int)
    resultDf['순수익'] = resultDf['순수익'].astype(int)
    

def calculate(input_csv_path: str, output_csv_path: str, year: int):
    
    # input_csv_path 을 읽어서 DataFrame 으로 만든다. DataFram의 모든 값은 string 으로 인식하도록 한다.
    # excel 에서 export된 csv 는 utf-8-sig 형태이다.
    # encoding = 'utf-8-sig'
    encoding = findEncoding(input_csv_path)
    df = pd.read_csv(input_csv_path, encoding=encoding, dtype=str)

    buyTxDic = {}

    # df 의 모든 값들을 strip() 하기
    df = df.applymap(lambda x: x.strip() if isinstance(x, str) else x)

    # 매수만 추출. 공모주입고는 공모주를 매수했다는 의미.
    buyDf = df[df['적요명'].isin(['매수', '공모주입고'])][['거래일자', '거래구분', '종목코드', '종목명', '수량', '단가', '수수료', '세금합계']]

    # construct buyTxDic where key is 종목코드 and value is list of Tx
    for index, buyRow in buyDf.iterrows():
        buyTx = BuyTx(buyRow)
        stockName: str = buyRow['종목코드']
        if stockName in buyTxDic:
            buyTxDic[stockName].append(buyTx)
        else:
            buyTxDic[stockName] = [buyTx]


    sellDf = df[df['적요명'].isin(['매도'])][['거래일자', '거래구분', '종목코드', '종목명', '수량', '단가', '수수료', '세금합계']]
    resultTxList = []

    for index, sellRow in sellDf.iterrows():
        DoneSellTxRow = False
        
        sellTx = SellTx(sellRow)
        print(sellTx)
        
        buyTxList = buyTxDic[sellTx.종목코드]
        print("initial) buyTxList, len=", len(buyTxList))

        for buyTx in buyTxList:
            print(buyTx)
            
            if buyTx.남은수량 <= sellTx.남은수량:
                resultTxList.append(ResultTx(buyTx, sellTx, buyTx.남은수량))
                sellTx.남은수량 -= buyTx.남은수량
                buyTx.남은수량 = 0
                
                print("\tcase 1)", sellTx.수량, buyTx.수량)
                
                if sellTx.남은수량 == 0:
                    DoneSellTxRow = True
                
            else:   # buyTx.남은수량 > sellTx.남은수량:
                resultTxList.append(ResultTx(buyTx, sellTx, sellTx.남은수량))
                buyTx.남은수량 -= sellTx.남은수량
                DoneSellTxRow = True

                print("\tcase 1)", sellTx.수량, buyTx.수량)
                
            if DoneSellTxRow:
                break
        
        # remove any buyTx from buyTxList if buyTx.수량 == 0
        buyTxList = [buyTx for buyTx in buyTxList if buyTx.남은수량 > 0]
        
        # print each items in buyTxList
        print("buyTxList, len=", len(buyTxList))
        for buyTx in buyTxList:
            print("\t", buyTx)
        
        if len(buyTxList) == 0:
            del buyTxDic[sellTx.종목코드]
        else:
            buyTxDic[sellTx.종목코드] = buyTxList
            print("buyTxDic[sellTx.종목명], len=", len(buyTxDic[sellTx.종목코드]), sellTx.종목코드)
            
        print()        

    # write resultTxList to csv. make first line as header
    resultDf = pd.DataFrame([resultTx.__dict__ for resultTx in resultTxList])
    
    # resultDf['매도거래일자'] 가 "2023" 으로 시작하는 경우에만 저장한다.
    resultDf = resultDf[resultDf['매도거래일자'].str.startswith(str(year))]
    
    setResultDType(resultDf)

    # utf-8 bom 형식으로 저장해야 엑셀에서 한글이 깨지지 않는다.
    encoding = 'utf-8-sig'
    resultDf.to_csv(output_csv_path, encoding=encoding, index=False, header=True)

if __name__ == "__main__":
    input = '/mnt/c/Users/labsu/Documents/tax/2023 (24년에 보고)/하나증권_거래내역_28767677-110_위탁계좌.csv'
    output = '/mnt/c/Users/labsu/Documents/tax/2023 (24년에 보고)/하나증권_거래내역_28767677-110_TAX보고형태.csv'
    result = calculate(input, output, 
                       TAX_YEAR)
    print(f'output: {result}')
    
    print()
    print('적요명 컬럼의 [배당금]이 있는지 확인하고 수작업으로 보고하는것을 잊지 마시라')




