# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -Iinclude -Itest

ifdef DISABLE_SIZE_CHECKS
CXXFLAGS += -DDISABLE_SIZE_CHECKS
endif

# Dirs
SRCDIR = src
TESTDIR = test
BUILDDIR = build
BINDIR = bin

# Target executable
TARGET = $(BINDIR)/ember

# Source and object files
SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(wildcard $(SRCDIR)/*.cpp))
MAIN_SOURCE = $(SRCDIR)/main.cpp
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Test sources and binaries
TEST_SOURCES = $(wildcard $(TESTDIR)/*_test.cpp)
TEST_OBJECTS = $(patsubst $(TESTDIR)/%.cpp, $(BUILDDIR)/%.test.o, $(TEST_SOURCES))
TEST_BINARIES = $(patsubst $(TESTDIR)/%.cpp, $(BINDIR)/test_%, $(TEST_SOURCES))

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS) $(BUILDDIR)/main.o
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compile main.o separately
$(BUILDDIR)/main.o: $(MAIN_SOURCE)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling source objects
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for test objects
$(BUILDDIR)/%.test.o: $(TESTDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link test binaries
$(BINDIR)/test_%: $(BUILDDIR)/%.test.o $(OBJECTS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Clean up build artifacts
clean:
	rm -rf $(BUILDDIR) $(BINDIR)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Make all tests
tests: $(TEST_BINARIES)

# Run all tests
test: tests
	@echo "Running tests..."
	@for test_binary in $(TEST_BINARIES); do \
		$$test_binary; \
	done

# Phony targets
.PHONY: all test clean run
