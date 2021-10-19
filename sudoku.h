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
bool findEmptyPos(char position[2], char board[9][9]);
bool isDup(char digit, char position[2], char board[9][9]);
bool isDupInRow(char digit, char row, char board[9][9]);
bool isDupInCol(char digit, char row, char board[9][9]);
bool isDupInSub(char digit, char position[2], char board[9][9]);
bool isValidDigit(char digit);
bool isValidPos(char position[2]);
int countDigits(char board[9][9]);

#endif
