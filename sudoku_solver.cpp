#include "sudoku_solver.hpp"
#include <sstream>

namespace sudoku_solver {

const int Puzzle::EMPTY;

Puzzle::Puzzle() : 
	_puzzle()
{
	read();
}

Puzzle::Puzzle(std::string file) : 
	_puzzle()
{
	read_from_file(file);
}

Puzzle::Puzzle(int argc, char **argv) : 
	_puzzle()
{
	if (argc > 1) {
		std::string param1{argv[1]};

		if (param1.find("-f") != std::string::npos) {
			read_from_file(argv[2]);
		} 
	} else {
			read(std::cin);
	}
}

bool 
Puzzle::read_from_file(std::string file) 
{
	std::ifstream ifs{file};
	if (!ifs) {
		std::cerr << "file could not be loaded: " 
			<< file << std::endl;
		exit(1);
	}
	return read(ifs);
}

bool 
Puzzle::read()
{
	return read(std::cin);
}

bool 
Puzzle::read(std::istream& is)
{
	std::string line;
	// is>>std::ws removes beginning white spaces
	while (std::getline(is>>std::ws, line)) {
		if (line[0] == '#')
			continue;
		std::istringstream iss(line);
		// retrive size of sudoku
		iss >> block_size;
		size = block_size*block_size;
		break;
	}
	// read fixed numbers. 0 are cells which empty
	while (std::getline(is>>std::ws, line)) {
		if (line[0] == '#')
			continue;
		// std::cout << line << std::endl; // debug
		std::istringstream iss(line);

		std::vector<int> _p(size);
		int p, c=0;
		while (iss >> p)
			_p[c++] = p;
		_puzzle.push_back(_p);
	}

	// TODO:
	return true;
}


void
Puzzle::print()
{
	std::string block_s = "";
	for (int i=0; i<2*block_size+1; i++)
		block_s += "-";
	block_s += "+";
	std::string row_sep = "+";
	for (int i=0; i<block_size; i++)
		row_sep += block_s;
	row_sep += "\n";
	int nrow=1, ncol=1;
	std::cout << row_sep;
	for (const auto& row : _puzzle) {
		ncol = 1;
		std::cout << "| ";
		for (const auto& col : row) {
			if (col == EMPTY)
				std::cout << '.';
			else
				std::cout << col;
			if (ncol % block_size)
				std::cout << " ";
			else
				std::cout << " | ";
			ncol++;
		}
		std::cout << std::endl;
		if(!(nrow % block_size))
			std::cout << row_sep;
		nrow++;
	}
}

bool 
Puzzle::hasEmptyCells() {
	for (const auto& row : _puzzle) {
		for (const auto& col : row) {
			if ( col == EMPTY) {
				return true;
			}
		}
	}
	return false;
}	

void 
Puzzle::solve()
{
	// std::cout << "start solving\n";
	for (int r=0; r<size; r++) {
		for (int c=0; c<size; c++) {
			if (_puzzle[r][c] == EMPTY) {
				for (int candidate=1; candidate <= size; candidate++) {
					// std::cout << OUTPUT(r) << ", "
					// 		<< OUTPUT(c) << ", "
					// 		<< OUTPUTLN(candidate);
					// if (CANDIDATE_FLAGS[candidate] & _candidates[r][c]) {
						_puzzle[r][c] = candidate;
						// print();	
						// std::cout << "\n";	
						if (isValid()) {
							// removeCandidate(r, c, candidate)
							solve();
							if (!hasEmptyCells())
								return;
						}
					// }
					// addCandidate(r, c, candidate);
				}
				_puzzle[r][c] = EMPTY;
			}
		}
	}
}

bool
Puzzle::isValid()
{
	for (int n=0; n<size; n++) {
		if (!(
			isRowValid(n) && 
			isColValid(n) &&
			isBlockValid(n)
			))
			return false;
	}
	return true;
}

bool 
Puzzle::isColValid(int ncol)
{
	std::map<int, int> m;
	for (int r = 0; r < size; r++) {
		int num = _puzzle[r][ncol];
		if (num != EMPTY) {
			if (++m[num] > 1) {
				// std::cout << "col not valid \n"<<
				// 	OUTPUTLN(r) << OUTPUTLN(ncol) <<
				// 	OUTPUTLN(num) << OUTPUTLN(m[num]);
				return false;
			}
		}
	}
	return true;
}


bool 
Puzzle::isRowValid(int nrow)
{
	std::map<int, int> m;
	for (int c = 0; c < size; c++) {
		int num = _puzzle[nrow][c];
		if (num != EMPTY) {
			if (++m[num] > 1) {
				// std::cout << "row not valid \n"<<
				// 	OUTPUTLN(c) << OUTPUTLN(nrow) <<
				// 	OUTPUTLN(num) << OUTPUTLN(m[num]);
				return false;
			}
		}
	}
	return true;
}

bool 
Puzzle::isBlockValid(int nblock)
{
	int c1 = block_size * (nblock % block_size);
	int c2 = c1+block_size;

	// std::cout << OUTPUT(c1) << ", " << OUTPUT(c2) << std::endl;

	int r1 = block_size * (nblock/block_size);
	int r2 = r1+block_size;

	// std::cout << OUTPUT(r1) << ", " << OUTPUT(r2) << std::endl;

	std::map<int, int> m;
	for (int r=r1; r < r2; r++) {
		for (int c=c1; c < c2; c++) {
			int num = _puzzle[r][c];
			if (num != EMPTY) {
				if(++m[num] > 1)
					return false;
			}
			// std::cout << _puzzle[r][c] << " ";
		}
		// std::cout << std::endl;
	}
	return true;
}

} // namespace sudoku_solver {