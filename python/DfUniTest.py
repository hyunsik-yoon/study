import pandas as pd
import unittest
from typing import List

import util as util

def get_wrong_numeric_row(actual_df, expected_df, 컬럼: str, 허용오차: int) -> str:
    for idx, (val1, val2) in enumerate(zip(actual_df[컬럼], expected_df[컬럼])):
        
        if abs(val1 - val2) > 허용오차:
            return f'actual: {val1} vs expected: {val2}'

def get_wrong_str_row(actual_df, expected_df, 컬럼: str) -> str:
    for idx, (val1, val2) in enumerate(zip(actual_df[컬럼], expected_df[컬럼])):
        if val1 != val2:
            return f'actual: {val1} vs expected: {val2}'

class DfUnitTest(unittest.TestCase):
    # TODO 110 unittest 도 이 함수를 이용하도록 refactiring할 것    
    
    def compare_columns_with_error_margin(self, actual_csv, expected_csv, 
                                            int컬럼들: List[str], 오차허용컬럼들: List[str],
                                            float컬럼들: List[str]):
        '''
        error margin에 대해서는 hana_110_tax.py의 주석을 참조한다.
        '''
        actual_encoding = util.findEncoding(actual_csv)
        expected_encoding = util.findEncoding(expected_csv)

        actual_df = pd.read_csv(actual_csv, encoding=actual_encoding, dtype=str)
        expected_df = pd.read_csv(expected_csv, encoding=expected_encoding, dtype=str)

        ColumnDtype = util.ColumnDtype(None, None, int컬럼들, float컬럼들)

        actual_df = util.changeColumnDtype(actual_df, ColumnDtype)
        expected_df = util.changeColumnDtype(expected_df, ColumnDtype)

        self.assertEqual(actual_df.shape, expected_df.shape)

        # 열의 개수와 이름이 같은지 확인
        self.assertEqual(actual_df.columns.tolist(), expected_df.columns.tolist())

        # 각 열을 개별적으로 비교
        for column_name in actual_df.columns:
            
            actual_values = actual_df[column_name]
            expected_values = expected_df[column_name]

            허용오차 = 1 if column_name in 오차허용컬럼들 else 0 

            if column_name in int컬럼들 or column_name in float컬럼들:
                comparison = abs(actual_values - expected_values) <= 허용오차
                self.assertTrue(comparison.all(), f'check {column_name}, {get_wrong_numeric_row(actual_df, expected_df, column_name, 허용오차)}')  
            else:
                comparison = (actual_values == expected_values)
                self.assertTrue(comparison.all(), f'check {column_name}, {get_wrong_str_row(actual_df, expected_df, column_name)}')                
