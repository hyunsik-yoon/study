#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

// 36_Valid_Sudoku

// https://leetcode.com/problems/valid-sudoku/description/

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<bool> marker(10);

         auto init_new_check = [&marker]() {
             // REMEMBER
             // std::fill
             // or
             // fill_n(vect.begin(), count, init_val);
             std::fill(marker.begin(), marker.end(), false);
         };

        // check each raw
        for (int row = 0; row < 9; row++)
        {
            init_new_check();
            for (int col = 0; col < 9; col++)
            {
                if (board[row][col] == '.') continue;
                int val = board[row][col] - '0';

                if (marker[val]) return false;
                else marker[val] = true;
            }
        }

        // check each col
        for (int col = 0; col < 9; col++)
        {
            init_new_check();
            for (int row = 0; row < 9; row++)
            {
                if (board[row][col] == '.') continue;
                int val = board[row][col] - '0';

                if (marker[val]) return false;
                else marker[val] = true;
            }
        }

        auto check_3x3_box = [&marker, &board](int start_row, int start_col) -> bool {
            for (int row = start_row; row < start_row + 3; row++)
            {
                for (int col = start_col; col < start_col + 3; col++)
                {
                if (board[row][col] == '.') continue;
                    int val = board[row][col] - '0';

                    if (marker[val]) return false;
                    else marker[val] = true;
                }
            }
            return true;
        };

        // check each 3x3 box
        for (int col = 0; col < 9; col += 3)
        {
            for (int row = 0; row < 9; row += 3)
            {
                init_new_check();
                if (check_3x3_box(row, col) == false)
                    return false;
            }
        }

        return true;
    }
};
