CROSS_COMPILE = aarch64-linux-gnu-

CXX=$(CROSS_COMPILE)g++
CXXFLAGS=-std=c++11
OBJ=*.o
SRC=*.cpp
EXE=main
all:$(EXE)
$(EXE):$(OBJ)
    $(CXX) $(CXXFLAGS) -o $@ $?
$(OBJ):$(SRC)
    $(CXX) $(CXXFLAGS) -c $^
clean:
    rm -f $(EXE)
    rm -f $(OBJ)