
CC = gcc
CXX = g++
CFLAGS = -Wall -fopenmp -std=c++0x

LFLAGS = -L/opt/OpenBLAS/lib -Wl,-rpath=/opt/OpenBLAS/lib

INCLUDES = -I./inc \
	-I/opt/OpenBLAS/include

LIBS = -lopenblas

SRC_TEST = tests/TestVec.cpp \
			tests/TestFullMat.cpp
SRC_BENCH = bench/BenchVec.cpp

SRC_PROGRAM = program/jsongraph.cpp

OBJ_TEST = $(SRC_TEST:.cpp=.o)
OBJ_BENCH = $(SRC_BENCH:.cpp=.o)
OBJ_PROGRAM = $(SRC_PROGRAM:.cpp=.o)

EXE_TEST = $(SRC_TEST:.cpp=)
EXE_BENCH = $(SRC_BENCH:.cpp=)
EXE_PROGRAM = $(SRC_PROGRAM:.cpp=)

test: $(EXE_TEST)

program: $(EXE_PROGRAM)

clean:
	rm -rf $(EXE_PROGRAM)
	rm -rf $(EXE_BENCH)
	rm -rf $(EXE_TEST)
	rm -rf $(OBJ_PROGRAM)
	rm -rf $(OBJ_BENCH)
	rm -rf $(OBJ_TEST)

$(EXE_TEST): %: %.o 
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@ $(LFLAGS) $(LIBS)

$(EXE_PROGRAM): %: %.o
	$(CXX) $(CFLAGS) $(INCLUDES) $< -o $@ $(LFLAGS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@
