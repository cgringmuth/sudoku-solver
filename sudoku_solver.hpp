#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>

#define OUTPUT(x) #x << "= " << (x)
#define OUTPUTLN(x) OUTPUT(x) << "\n"

// static const int BLOCK_SIZE = 3;
// static const int SIZE = BLOCK_SIZE*BLOCK_SIZE;

namespace sudoku_solver {

class Puzzle {
	typedef std::vector< std::vector<int> > Matrix;
	static const int EMPTY = 0;

public:
	// constructor
	Puzzle();
	Puzzle(std::string file);
	Puzzle(int argc, char **argv);

	bool read(std::istream& is);
	bool read();
	bool read_from_file(std::string file);

	void solve();
	bool isValid();
	bool isRowValid(int nrow);
	bool isColValid(int ncol);
	bool isBlockValid(int nblock);
	bool hasEmptyCells();

	void print();

private:
	Matrix _puzzle;
	int size;
	int block_size;
};

} // namespace sudoku_solver