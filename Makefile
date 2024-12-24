# Compiler and linker settings
CXX = g++
CXXFLAGS = -std=c++17 -w -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

# Project structure
SRCDIR = .
BUILDDIR = .
EXEC = Mazerunner

# Find all source files (only including main.cpp for compilation)
SRC = main.cpp
OBJ = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SRC))

# Object files that need to be linked but not recompiled
EXTRA_OBJ = map.o player.o render.o

# Default target
all: $(EXEC)

# Build executable by compiling main.cpp and linking with object files
$(EXEC): $(OBJ) $(EXTRA_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build object files (only for main.cpp)
$(BUILDDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(BUILDDIR)/*.o $(EXEC)

# Run the program
run: all
	./$(EXEC)
