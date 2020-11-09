# Simple makefile for compiling Matrix Homework and executing

# Default it should already call all - but it doesn't hurt to be explicit
.PHONY = all

CXX = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CXXFLAGS  = -g -Wall -O2 -std=gnu++14

# 
TARGET = hw1.out

DEPS = src/Matrix.cpp src/MatrixMenu.cpp

all: $(TARGET) test_runner
	@echo  "Executing test_runner..."
	@./test_runner
	@echo
	@echo "Test Complete: Executing Main Binary"
	@echo
	@echo "Executing hw1.out..."
	@./$(TARGET) -f assets/data.txt

$(TARGET): $(DEPS)
	@echo "Compiling source..."
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(DEPS) src/main.cpp -lgtest -lgtest_main -lpthread
	@echo "..Source compiled successfully"

test_runner: unitTest/Matrix_test.cpp
	@echo "Compiling unit test..."
	@$(CXX) $(CXXFLAGS) -o test_runner unitTest/Matrix_test.cpp unitTest/test_main.cpp -lgtest -lgtest_main -lpthread
	@echo "...Unit test compiled successfully"

clean:
	$(RM) $(TARGET) test_runner 
