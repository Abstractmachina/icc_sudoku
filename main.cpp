#include <iostream>
#include <cstdio>
#include "sudoku.h"

using namespace std;

int main() {

	char board[9][9];

	/* This section illustrates the use of the pre-supplied helper functions. */
	cout << "============= Pre-supplied functions =============\n\n";

	cout << "Calling load_board():\n";
	load_board("easy.dat", board);

	cout << '\n';
	      cout << "Displaying Sudoku board with display_board():\n";
	display_board(board);
	cout << "Done!\n\n";

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			cout << char(board[row][col]) << " ";
			//printf("%i col %i: %i\n", row, col,char(board[row][col]));
		}
		cout << endl;
	}


	cout << "=================== Question 1 ===================\n\n";

	load_board("easy.dat", board);
	cout << "Board is ";
	if (!is_complete(board)) {
	  cout << "NOT ";
	}
	cout << "complete.\n\n";

	load_board("easy-solution.dat", board);
	cout << "Board is ";
	if (!is_complete(board)) {
	  cout << "NOT ";
	}
	cout << "complete.\n\n";
	cout << "=================== Question 2 ===================\n\n";

	load_board("easy.dat", board);

	// Should be OK
	cout << "Putting '1' into I8 is ";
	if (!make_move("I8", '1', board)) {
	  cout << "NOT ";
	}
	cout << "a valid move. The board is:\n";
	display_board(board);

	// write more tests

	cout << "=================== Question 3 ===================\n\n";
	
	load_board("easy.dat", board);
	if (save_board("easy-copy.dat", board)) {
	  cout << "Save board to 'easy-copy.dat' successful.\n";
	} else {
	  cout << "Save board failed.\n";
	}
	cout << '\n';

	cout << "=================== Question 4 ===================\n\n";

	load_board("easy.dat", board);
	if (solve_board(board)) {
	  cout << "The 'easy' board has a solution:\n";
	} else {
	  cout << "A solution cannot be found.\n";
	}
	cout << '\n';
	  display_board(board);

	load_board("medium.dat", board);
	if (solve_board(board)) {
	  cout << "The 'medium' board has a solution:\n";
	  display_board(board);
	} else {
	  cout << "A solution cannot be found.\n";
	}
	cout << '\n';

  	// write more tests

  	cout << "=================== Question 5 ===================\n\n";
  	// write more tests
	//To determine difficulty, the amount of pre-filled digits is counted. 
	//the lower the number, the harder the sudoku.

	load_board("mystery1.dat", board);
	cout << "Mystery 1 has " << countDigits(board) << " pre-filled digits.\n";
	if (solve_board(board)) 
	{
		cout << "Mystery 1 has a solution.\n";
    		display_board(board);
	}

	load_board("mystery2.dat", board);
	cout << "Mystery 2 has " << countDigits(board) << " pre-filled digits.\n";
	if (solve_board(board)) 
	{
		cout << "Mystery 2 has a solution.\n";
		display_board(board);
	}
	
	load_board("mystery3.dat", board);
	cout << "Mystery 3 has " << countDigits(board) << " pre-filled digits.\n";
	if (solve_board(board)) 
	{
		cout << "Mystery 3 has a solution.\n";
    		display_board(board);
	}

	//checking numbers of easy and medium sudoku for reference.
	load_board("easy.dat", board);
	cout << "Easy has " << countDigits(board) << " pre-filled digits.\n";
	load_board("medium.dat", board);
	cout << "Medium has " << countDigits(board) << " pre-filled digits.\n";

	cout << "\n************Alternative difficulty testing **********\n\n";
	cout << "Counting the number of cycles it takes for the recursive function"; 
	cout << "to solve the board rather than the number of pre-filled slots.\n\n";

	int stepCounter = 0;
	load_board("mystery1.dat", board);
	if (solve_board(board, stepCounter)) 
	{
		cout << "Mystery 1 has a solution.\n";
		display_board(board);
		cout << "\nIt took " << stepCounter << " steps to solve.\n\n";
	}
	stepCounter = 0;
	load_board("mystery2.dat", board);
	if (solve_board(board, stepCounter)) 
	{
		cout << "Mystery 2 has a solution.\n";
		display_board(board);
		cout << "\nIt took " << stepCounter << " steps to solve.\n\n";
	}
	stepCounter = 0;
	load_board("mystery3.dat", board);
	if (solve_board(board, stepCounter)) 
	{
		cout << "Mystery 3 has a solution.\n";
		display_board(board);
		cout << "\nIt took " << stepCounter << " steps to solve.\n\n";
	}
	
	return 0;
}
