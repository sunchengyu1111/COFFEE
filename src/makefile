.PHONY: all  clean
SRC=$(wildcard *.cpp)
BIN=$(SRC:%.cpp=%)

MPI_CC=mpic++ -O2 -mavx

all:$(BIN)

$(BIN):%:%.cpp
	$(MPI_CC) $^ -o $@

clean:
