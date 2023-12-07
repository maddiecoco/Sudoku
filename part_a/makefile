# Makefile for Project 2: Flip card game

# Define the compiler and compilation flags
CXX = g++
CXXFLAGS = -std=c++11

# Define the source and header files
SRCS = main.cpp board.cpp
HEADERS = d_except.h d_matrix.h

# Define the target executable
TARGET = main

# Default target: compile and run the program
all: run

# Compile the source files into the executable
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Run the compiled program
run: $(TARGET)
	./$(TARGET)

# Clean up the executable
clean:
	rm -f $(TARGET)