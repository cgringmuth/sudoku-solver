CXXFLAGS += -Wall -Werror -std=c++11 -O3
CXXFLAGS += -I.
# LDFLAGS += -lm

SOURCE = \
    sudoku_solver.cpp \
    sudoku_solver.hpp \
    main.cpp \

all: sudoku

sudoku: $(SOURCE)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(SOURCE) -o sudoku
