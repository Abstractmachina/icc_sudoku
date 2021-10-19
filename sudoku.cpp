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
bool is_complete(char board[9][9])
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//if val is anything but a number
			if (board[row][col] < 48 || board[row][col] > 57 ) return false;
		}
	}
	return true;
}

bool make_move(char position[2], char digit, char board[9][9])
{

	printf("DEBUG | position 0: %c, psotion 1: %c, digit: %c\n", 
			position[0], position[1], digit);
	//checking for valid position
	if (	position[0] < 65 || position[0] > 73 || 
		position[1] < 49 || position[1] > 57	)
	{
		return false;
	}
	//checking for valid digit
	if (digit < 49 || digit > 57) return false;
	//checking for dup in row
	for (int col =0; col < 9; col++)
	{
		if (board[position[0] - 'A'][col] == digit) 
			return false;
	}		
	//checking for dup in col
	for (int row = 0; row < 9; row++)
	{
		if (board[row][position[1] - 49] == digit) 
			return false;
	}		

	//if all checks passed, update value at position
	board[position[0] - 'A'][position[1] - 49] = digit;

	return true;
}

bool save_board(const char* filename, char board[9][9])
{
	ofstream out;
	out.open(filename);

	if (out.fail())
	{
		cout << "Save unsuccessful!\n";
		return false;
	}

	for(int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			out << board[row][col];
		}
		out << endl;
	}

	out.close();


	return true;
}
