#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "sudoku.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* pre-supplied function to load a Sudoku board from a file */
void load_board(const char* filename, char board[9][9]) {

  cout << "Loading Sudoku board from file '" << filename << "'... ";

  ifstream in(filename);
  if (!in) {
    cout << "Failed!\n";
  }
  assert(in);

  char buffer[512];

  int row = 0;
  in.getline(buffer,512);
  while (in && row < 9) {
    for (int n=0; n<9; n++) {
      assert(buffer[n] == '.' || isdigit(buffer[n]));
      board[row][n] = buffer[n];
    }
    row++;
    in.getline(buffer,512);
  }

  cout << ((row == 9) ? "Success!" : "Failed!") << '\n';
  assert(row == 9);
}

/* internal helper function */
void print_frame(int row) {
  if (!(row % 3)) {
    cout << "  +===========+===========+===========+\n";
  } else {
    cout << "  +---+---+---+---+---+---+---+---+---+\n";
  }
}

/* internal helper function */
void print_row(const char* data, int row) 
{
 	 cout << (char) ('A' + row) << " ";
	 for (int i=0; i<9; i++) 
	 {
		 cout << ( (i % 3) ? ':' : '|' ) << " ";
		 cout << ( (data[i]=='.') ? ' ' : data[i]) << " ";
	 }
	 cout << "|\n";
}

/* pre-supplied function to display a Sudoku board */
void display_board(const char board[9][9]) {
  cout << "    ";
  for (int r=0; r<9; r++) {
    cout << (char) ('1'+r) << "   ";
  }
  cout << '\n';
  for (int r=0; r<9; r++) {
    print_frame(r);
    print_row(board[r],r);
  }
  print_frame(9);
}

/* add your functions here */
/********************************************************/
bool is_complete(char board[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//if val is anything but 1 - 9
			if (!isValidDigit(board[row][col])) return false;
			//if (board[row][col] < 48 || board[row][col] > 57 ) return false;
		}
	}
	return true;
}

//
bool make_move(char position[2], char digit, char board[9][9])
{

	//printf("DEBUG | position 0: %c, psotion 1: %c, digit: %c\n", 
	//		position[0], position[1], digit);
	
	//check for valid input	
	if (!isValidPos(position) || !isValidDigit(digit)) return false;
	//check for duplicate number
	if (	isDupInRow(digit, position[0], board) || 
		isDupInCol(digit, position[1], board)	) 
		return false;

	//if all checks passed, update value at position
	board[position[0] - 'A'][position[1] - 49] = digit;

	return true;
}

//
bool save_board(const char* filename, char board[9][9])
{
	//init out stream
	ofstream out;
	out.open(filename);

	//check if file opened successfully
	if (out.fail())
	{
		cout << "Save unsuccessful!\n";
		return false;
	}

	//write board to file
	for(int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			out << board[row][col];
		}
		out << endl;
	}

	//close file
	out.close();

	return true;
}

bool solve_board(char board[9][9])
{
	char position[2];
        if (!findEmptyPos(position, board)) //find first empty position
		return true; 
	//if there are no empty positions, 
	//it means the board is complete. thus return true.
	
	for (char digit = '1'; digit <= '9'; digit++) //check for all possible values
	{
		if (!isDup(digit, position, board)) //if value passes all duplicate conditions
		{
			board[position[0] - 'A'][position[1] - '1'] = digit;
			if (!solve_board(board)) //go to next empty position recursively.
			{
				//if a solution could not be found, 
				//reset value and move to next digit
				board[position[0] - 'A'][position[1] - '1'] = '.'; 
				continue;
			} else return true;

		} else { ; } //if duplicate, do nothing and move on to next digit

	}
	return false;
	//return false if no viable digits have been found and board is not complete,
	//thus returning to previous stack frame 
}



/***************	UTILITY FUNCTIONS	******************/


//Find the first empty position, iterating from top left to bottom right sequentially
bool findEmptyPos(char position[2], char board[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == '.')
			{
				position[0] = char(row + 'A');
				position[1] = char(col + '1');
				return true;
			}
		}
	}
	return false;
}

//check for all duplicate conditions
bool isDup(char digit, char position[2], char board[9][9])
{
	if (	isDupInRow(digit, position[0], board) || 
		isDupInCol(digit, position[1], board) || 
		isDupInSub(digit, position, board)	) return true;
	else return false;
}
//Assumes row is signified by a letter A - I.
bool isDupInRow(char digit, char row, char board[9][9])
{
	for (int col =0; col < 9; col++)
	{
		if (board[row - 'A'][col] == digit) 
			return true;
	}		
	return false;
}

//Assumes col is signified by a char number 1 - 9
bool isDupInCol(char digit, char col, char board[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		if (board[row][col - 49] == digit) 
			return true;
	}
	return false;
}

bool isDupInSub(char digit, char position[2], char board[9][9])
{
	int subX = 3 * ((position[0] - 'A') / 3); //start of x domain
	int subY = 3 * ((position[1] - '1') / 3); //start of y domain
	
	//check for dup number in sub-square
	for (int x = subX; x < subX + 3; x++)
	{
		for (int y = subY; y < subY + 3; y++)
		{
			if (board[x][y] == digit) return true;
		}
	}	

	return false;
}

bool isValidDigit(char digit)
{
	if (digit < 49 || digit > 57) return false;
	else return true;
}

bool isValidPos(char position[2])
{
	if (position[0] < 65 || position[0] > 73 || position[1] < 49 || position[1] > 57)
		return false;
       	else return true;
}

int countDigits(char board[9][9])
{
	int count = 0;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (isValidDigit(board[row][col])) count++;
		}
	}
	return count;
}
