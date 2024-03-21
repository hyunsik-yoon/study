import hana_210_tax as tax210
import DfUniTest as DfUnitTest
import util as util

import unittest
import pandas as pd
from typing import List

class Test210(DfUnitTest.DfUnitTest):
    
    def test_files(self):
        test_files = [
                      './test/210_국내선물_01.csv',
                      './test/210_국내선물_02.csv',
                      './test/210_국내선물_03.csv',
                      './test/210_국내선물_04.csv',
                      './test/210_국내선물_05.csv',
                      './test/210_국내선물_06.csv',
                    ]
        expected = [
                    './test/210_국내선물_01_expected.csv',
                    './test/210_국내선물_02_expected.csv',
                    './test/210_국내선물_03_expected.csv',
                    './test/210_국내선물_04_expected.csv',
                    './test/210_국내선물_05_expected.csv',
                    './test/210_국내선물_06_expected.csv',
                    ]
        actual = '/home/eric/work/study/z/output.csv'    
        for i in range(0, len(test_files)):
            print(f'** testing {test_files[i]} **')
            tax210.generate_tax_file(test_files[i], actual, TAX_YEAR)
            print(actual, expected[i])

            intColumns = ['거래수량', ]
            오차허용Columns = ['총수수료', '순수익']
            float컬럼들 = ['진입단가', '청산단가', '순수익', '총수수료', '총세금합계'] 

            self.compare_columns_with_error_margin(actual, expected[i], intColumns, 오차허용Columns, float컬럼들)

'''
note 1)
  actual_csv 의 행과 expected_csv 행을 1:1 비교한다.
  따라서 두 파일의 행의 데이터가 일치해야 한다. (행이 뒤섞이면 test는 fail 함)
  이것은... 각 행에 대한 key를 만들 수 없어서 그렇당..  
'''

TAX_YEAR = 2023

if __name__ == '__main__':
    unittest.main()       
