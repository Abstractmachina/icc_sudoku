#ifndef SUDOKU_H
#define SUDOKU_H

void load_board(const char* filename, char board[9][9]);
void display_board(const char board[9][9]);

/* functions to be assessed */

///checks if all spaces on board have been filled
bool is_complete(char board[9][9]);

//attempt to place digit on board. returns false if position is out of bound
//and digit is invalid or already exists in row/column.
bool make_move(char position[2], char digit, char board[9][9]);

//save board to .dat file.
bool save_board(const char* filename, char board[9][9]);

//check if a solution can be found.
bool solve_board(char board[9][9]);


/*****************	UTILITY FUNCTIONS	*******************/
//Find the first empty position, iterating from top left to bottom right sequentially.
////updates position with found values.
bool findEmptyPos(char position[2], char board[9][9]);
//check for all duplicate conditions
bool isDup(char digit, char position[2], char board[9][9]);
//check for duplicates in row. Assumes 'A' - 'I'
bool isDupInRow(char digit, char row, char board[9][9]);
//check for duplicates in column. Assumes '1' - '9'
bool isDupInCol(char digit, char row, char board[9][9]);
//check for duplicates in sub-square
bool isDupInSub(char digit, char position[2], char board[9][9]);
//check if digit is between 1 - 9.
bool isValidDigit(char digit);
//check if position is valid.
bool isValidPos(char position[2]);
//count number of filled in digits. Used to determine difficulty of sudoku.
int countDigits(char board[9][9]);

#endif
