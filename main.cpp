#include <vector>
#include <stdlib.h>
#include <iostream>

// set a constant grid size to 9
constexpr int gridSize = 9;

// function to determine weather the number is valid for row
bool isValidRow(std::vector < std::vector < int >> board, int row, int number) {
    for (int i = 0; i < gridSize; i++) {
        if (board[row][i] == number) {
            return true;
        }
    }
    return false;
}

// function to determine weather the number is valid for column
bool isValidColumn(std::vector < std::vector < int >> board, int column, int number) {
    for (int i = 0; i < gridSize; i++) {
        if (board[i][column] == number) {
            return true;
        }
    }
    return false;
}

// function to determine weather the number is valid for box
bool isValidBox(std::vector < std::vector < int >> board, int row, int column, int number) {
    // calculate starting indexes for the box
    int currentBoxRow = row - row % 3;
    int currentBoxColumn = column - column % 3;

    for (int i = currentBoxRow; i < currentBoxRow + 3; i++) {
        for (int j = currentBoxColumn; j < currentBoxColumn + 3; j++) {
            if (board[i][j] == number) {
                return true;
            }
        }
    }
    return false;
}

// combine the results of above 3 functions
bool isValidPlacement(std::vector < std::vector < int >> board, int row, int column, int number) {
    return !isValidRow(board, row, number) &&
        !isValidColumn(board, column, number) &&
        !isValidBox(board, row, column, number);
}


// recursive function to solve the board
bool solve(std::vector < std::vector < int >>& board) {
    for (int row = 0; row < gridSize; row++) {
        for (int column = 0; column < gridSize; column++) {
            if (board[row][column] == 0) {
                for (int num = 1; num <= gridSize; num++) {
                    if (isValidPlacement(board, row, column, num)) {
                        board[row][column] = num;
                        if (solve(board)) {
                            return true;
                        }
                        else {
                            board[row][column] = 0;
                        }
                    }
                }
                // return false if cannot solve the box
                return false;
            }
        }
    }
}

// function to print the board
void printBoard(std::vector < std::vector < int >> board) {
    for (int i = 0; i < gridSize; i++) {
        if (i % 3 == 0 && i != 0) {
            std::cout << "---------------------\n";
        }
        for (int j = 0; j < gridSize; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << "| ";
            }
            std::cout << board[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

// main function
int main() {
    // sample sudoku board data
    // 0 means empty
    std::vector < std::vector < int >> board = {
    {7, 0, 2,  0, 5, 0,  6, 0, 0},
    {0, 0, 0,  0, 0, 3,  0, 0, 0},
    {1, 0, 0,  0, 0, 9,  5, 0, 0},

    {8, 0, 0,  0, 0, 0,  0, 9, 0},
    {0, 4, 3,  0, 0, 0,  7, 5, 0},
    {0, 9, 0,  0, 0, 0,  0, 0, 8},

    {0, 0, 9,  7, 0, 0,  0, 0, 5},
    {0, 0, 0,  2, 0, 0,  0, 0, 0},
    {0, 0, 7,  0, 4, 0,  2, 0, 3}
    };

    std::cout << "Board: \n";
    std::cout << '\n';
    printBoard(board);
    std::cout << "Solving Sudoku Grid..." << '\n';

    if (solve(board)) {
        system("cls");
        std::cout << "Solved Successfully!\n";
        std::cout << '\n';
        printBoard(board);
    }
    else {
        std::cout << "Solved Unsuccessfully!\n";
    }
    return 0;
}
