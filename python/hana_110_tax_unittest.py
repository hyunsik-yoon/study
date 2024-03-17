import hana_110_tax as tax110
import pandas as pd

'''
note 1)
  actual_csv 의 행과 expected_csv 행을 1:1 비교한다.
  따라서 두 파일의 행의 데이터가 일치해야 한다. (행이 뒤섞이면 test는 fail 함)
  이것은... 각 행에 대한 key를 만들 수 없어서 그렇당..  
'''

TAX_YEAR = 2023

def compare_columns_with_error_margin(actual_csv, expected_csv):
    '''
    error margin에 대해서는 hana_110_tax.py의 주석을 참조한다.
    '''
    actual_encoding = tax110.findEncoding(actual_csv)
    expected_encoding = tax110.findEncoding(expected_csv)
    
    actual_df = pd.read_csv(actual_csv, encoding=actual_encoding, dtype=str)
    expected_df = pd.read_csv(expected_csv, encoding=expected_encoding, dtype=str)
    
    tax110.setResultDType(actual_df)
    tax110.setResultDType(expected_df)

    # 행의 수가 같은지 확인
    if actual_df.shape[0] != expected_df.shape[0]:
        return False
    
    # 열의 개수와 이름이 같은지 확인
    if actual_df.columns.tolist() != expected_df.columns.tolist():
        return False

    # 각 열을 개별적으로 비교
    for column_name in actual_df.columns:
        if column_name not in expected_df.columns:
            return False
        
        actual_values = actual_df[column_name]
        expected_values = expected_df[column_name]

        if actual_df[column_name].dtype == 'int' and expected_df[column_name].dtype == 'int':
            # 허용 가능한 오차 범위 내의 값이 있는지 확인
            if column_name in ['총수수료', '총세금합계', '순수익']:
                comparison = abs(actual_values - expected_values) <= 1
                if not comparison.all():
                    print('check 총수수료 or 총세금합계 or 순수익:', column_name)
                    return False
            else:
                comparison = (actual_values == expected_values)
                if not comparison.all():
                    print('check int that is NOT 총수수료 nor 총세금합계:', column_name)
                    return False
        else: # non int type
            comparison = (actual_values == expected_values)
            if not comparison.all():
                print('check non int type: ',column_name, actual_df[column_name].dtype)
                return False

    return True


def run_unit_tests():
    test_files = ['./test/110_위탁계좌_01.csv',
                  './test/110_위탁계좌_02.csv',
                  './test/110_위탁계좌_03.csv',
                  './test/110_위탁계좌_04.csv',
                  './test/110_위탁계좌_05.csv',
                  ]
    expected = ['./test/110_위탁계좌_01_expected.csv',
                './test/110_위탁계좌_02_expected.csv',
                './test/110_위탁계좌_03_expected.csv',
                './test/110_위탁계좌_04_expected.csv',
                './test/110_위탁계좌_05_expected.csv',
                ]
    actual = '/home/eric/work/study/z/output.csv'    
    for i in range(0, len(test_files)):
        tax110.calculate(test_files[i], actual, TAX_YEAR)
        print(actual, expected[i])
        assert compare_columns_with_error_margin(actual, expected[i])


if __name__ == "__main__":
    run_unit_tests()        
