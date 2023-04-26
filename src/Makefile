SRC := $(wildcard *.cpp)
SRC0 := $(filter-out %CPU.cpp, $(SRC))
SRC1 := $(filter %CPU.cpp, $(SRC))
OBJ0 = $(patsubst %.cpp, %.o, $(SRC0))
OBJ1 = $(patsubst %.cpp, %.o, $(SRC1))
BIN := COFFEE_serial COFFEE_C2R COFFEE_CPU MPI_Ring MPI_SALaR COFFEE_MPI_c COFFEE_MPI_d

CC = mpic++
CFLAGS0 = -O2 -mavx
CFLAGS1 = -mavx

.PHONY: all
all: $(BIN)

$(filter %serial, $(BIN)): $(patsubst %.cpp, %.o, $(filter %serial.cpp, $(SRC)))
	$(CC) $(CFLAGS0) $(patsubst %.cpp, %.o, $(filter %serial.cpp, $(SRC))) -o $(filter %serial, $(BIN))

$(filter %C2R, $(BIN)): $(patsubst %.cpp, %.o, $(filter %C2R.cpp, $(SRC)))
	$(CC) $(CFLAGS0) $(patsubst %.cpp, %.o, $(filter %C2R.cpp, $(SRC))) -o $(filter %C2R, $(BIN))

$(filter %CPU, $(BIN)): $(patsubst %.cpp, %.o, $(SRC1))
	$(CC) $(CFLAGS1) $(patsubst %.cpp, %.o, $(SRC1)) -o $(filter %CPU, $(BIN))

$(filter %Ring, $(BIN)): $(patsubst %.cpp, %.o, $(filter %Ring.cpp, $(SRC)))
	$(CC) $(CFLAGS0) $(patsubst %.cpp, %.o, $(filter %Ring.cpp, $(SRC))) -o $(filter %Ring, $(BIN))

$(filter %SALaR, $(BIN)): $(patsubst %.cpp, %.o, $(filter %SALaR.cpp, $(SRC)))
	$(CC) $(CFLAGS0) $(patsubst %.cpp, %.o, $(filter %SALaR.cpp, $(SRC))) -o $(filter %SALaR, $(BIN))

$(filter %MPI_c, $(BIN)): $(patsubst %.cpp, %.o, $(filter %MPI_c.cpp, $(SRC)))
	$(CC) $(CFLAGS0) $(patsubst %.cpp, %.o, $(filter %MPI_c.cpp, $(SRC))) -o $(filter %MPI_c, $(BIN))

$(filter %MPI_d, $(BIN)): $(patsubst %.cpp, %.o, $(filter %MPI_d.cpp, $(SRC)))
	$(CC) $(CFLAGS0) $(patsubst %.cpp, %.o, $(filter %MPI_d.cpp, $(SRC))) -o $(filter %MPI_d, $(BIN))

$(OBJ0): %.o: %.cpp
	$(CC) $(CFLAGS0) -c $^ -o $@

$(OBJ1): %.o: %.cpp
	$(CC) $(CFLAGS1) -c $^ -o $@

.PHONY: clean
clean:
	-rm -f *.o $(BIN)
