CC = gcc
CXX = g++
CFLAGS = -Wall -fopenmp

LFLAGS = -L/opt/OpenBLAS/lib

INCLUDES = 	-I./inc \
			-I/opt/OpenBLAS/include

LIBS = -lopenblas

SRC_TEST = tests/TestVec.cpp \
			tests/TestFullMat.cpp
SRC_BENCH = bench/BenchVec.cpp

OBJ_TEST = $(SRC_TEST:.cpp=.o)
OBJ_BENCH = $(SRC_BENCH:.cpp=.o)

DEP_TEST = $(SRC_TEST:.cpp=.d)
DEP_BENCH = $(SRC_TEST:.cpp=.d)

EXE_TEST = $(SRC_TEST:.cpp=)
EXE_BENCH = $(SRC_BENCH:.cpp=)

test: $(OBJ_TEST)
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $(OBJ_TEST) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@