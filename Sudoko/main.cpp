#include <iostream>
#include <vector>

using namespace std;

bool solveSudoku(vector<vector<int>>& grid);

bool findEmptyCell(vector<vector<int>>& grid, int& row, int& col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool isValidMove(vector<vector<int>>& grid, int row, int col, int num);

bool isValidInRow(vector<vector<int>>& grid, int row, int num) {
    for (int col = 0; col < 9; col++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool isValidInCol(vector<vector<int>>& grid, int col, int num) {
    for (int row = 0; row < 9; row++) {
        if (grid[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool isValidInBox(vector<vector<int>>& grid, int startRow, int startCol, int num);

void printGrid(vector<vector<int>>& grid) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> sudokuGrid = {
        {0, 7, 0, 0, 6, 0, 0, 0, 9},
        {6, 0, 0, 5, 0, 0, 0, 8, 0},
        {0, 0, 4, 0, 0, 0, 7, 0, 0},
        {0, 3, 0, 0, 0, 6, 0, 0, 0},
        {2, 0, 0, 0, 5, 0, 0, 0, 8},
        {0, 0, 0, 4, 0, 0, 0, 1, 0},
        {0, 0, 3, 0, 0, 0, 4, 0, 0},
        {0, 2, 0, 0, 0, 7, 0, 0, 3},
        {1, 0, 0, 0, 8, 0, 0, 2, 0}
    };

    if (solveSudoku(sudokuGrid)) {
        cout << "Solved Sudoku:" << endl;
        printGrid(sudokuGrid);
    }
    else {
        cout << "No solution exists." << endl;
    }

    return 0;
}

bool isValidInBox(vector<vector<int>>& grid, int startRow, int startCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (grid[row + startRow][col + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>>& grid) {
    int row, col;

    if (!findEmptyCell(grid, row, col)) {
        return true; // The puzzle is solved
    }

    for (int num = 1; num <= 9; num++) {
        if (isValidMove(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid)) {
                return true;
            }

            grid[row][col] = 0; // If the current configuration doesn't lead to a solution, backtrack
        }
    }

    return false;
}

bool isValidMove(vector<vector<int>>& grid, int row, int col, int num) {
    return isValidInRow(grid, row, num) &&
        isValidInCol(grid, col, num) &&
        isValidInBox(grid, row - (row % 3), col - (col % 3), num);
}
