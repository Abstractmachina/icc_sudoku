exec: main.o sudoku.o
	g++ -Wall main.o sudoku.o -o exec

main.o: main.cpp sudoku.h
	g++ -Wall -g -c main.cpp

sudoku.o: sudoku.cpp sudoku.h
	g++ -Wall -g -c sudoku.cpp sudoku.h

clean:
	rm -f *.o exec
