#include <iostream>
#include "sudoku_solver.hpp"

int
main(int argc, char **argv)
{
	sudoku_solver::Puzzle puzzle(argc, argv);
	puzzle.print();
	// cout << "\n\n";
	puzzle.solve();
	std::cout << "\n~~~~~~~~~~~~~~~\n\n";
	puzzle.print();

	// for (int b=0; b<SIZE; b++)
	// 	puzzle.isBlockValid(b);
}