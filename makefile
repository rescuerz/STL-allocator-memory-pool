# Makefile for compiling main.cpp, MyAllocator.cpp, and MyAllocator.h

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -O3 -g

# Target executable
TARGET = test

# Source files
SRCS = main.cpp MyAllocator.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Linking the target executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compiling source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild the project
rebuild: clean all

.PHONY: all clean rebuild
