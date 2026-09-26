# Compiler
CPP = g++

# Compiler flags
FLAGS = -Wall -Wextra -std=c++17

# Output executable name
TARGET = homework

# Source files
SRCS = main.cpp lib.cpp

# Object files (auto-generated)
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link step
$(TARGET): $(OBJS)
	$(CPP) $(FLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp -> .o
%.o: %.cpp lib.h
	$(CPP) $(FLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
