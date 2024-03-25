import pandas as pd
import chardet

from typing import List

class ColumnDtype:
    def __init__(self, 
                       date컬럼들: List[str], dateFormat: str, 
                       int컬럼들: List[str], 
                       float컬럼들: List[str]):
        self.date컬럼들 = date컬럼들
        self.dateFormat = dateFormat
        self.int컬럼들 = int컬럼들
        self.float컬럼들 = float컬럼들
        

def changeColumnDtype(df: pd.DataFrame, columnDtype: ColumnDtype) -> pd.DataFrame:
    # df 의 모든 값들을 strip() 하기
    df = df.applymap(lambda x: x.strip() if isinstance(x, str) else x)
    
    if columnDtype.date컬럼들 != None:
        assert columnDtype.dateFormat != None
        for column in columnDtype.date컬럼들:
            # '거래일자' 컬럼이 "2023-03-06" 형태로 되어 있는데, datetime 으로 변환한다.
            df[column] = pd.to_datetime(df[column], format=columnDtype.dateFormat)
        
    if columnDtype.int컬럼들 != None:
        for column in columnDtype.int컬럼들:
            df[column] = df[column].str.replace(',', '').astype(int)

    if columnDtype.float컬럼들 != None:
        for column in columnDtype.float컬럼들:
            df[column] = df[column].str.replace(',', '').astype(float)

    return df


def findEncoding(file_path: str) -> str:
    '''
    파일의 인코딩을 찾아 리턴한다.
    '''
    with open(file_path, 'rb') as f:
        result = chardet.detect(f.read())
    return result['encoding']
