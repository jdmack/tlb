CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
TESTDIR := tests
BUILDDIR := build
TARGET := tlb
TESTER := tester
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TESTS   := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJ := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TESTS:.$(SRCEXT)=.o)) $(filter-out build/main.o,$(OBJECTS))

CFLAGS := -g3 -O0 -std=c++0x #-Wall
LIB := -lSDL2 -lSDL2_image -static-libgcc 
TESTLIB := -L gtest/lib/.libs -lgtest -lgtest_main -lpthread
GTESTLIB := gtest/lib/libgtest.a
 
#LIB := -lSDL2 -lSDL2_image -lSDL_ttf -lSDL_mixer -static-libgcc

# Uncomment on CentOS 6 (GCC 4.4)
#CFLAGS += -Dnullptr='(NULL)'

INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/utils
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(TESTER)"; $(RM) -r $(BUILDDIR) $(TARGET) $(TESTER)

# Tests
$(BUILDDIR)/%.o: $(TESTDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

# Tester - test driver and main
$(TESTER): $(OBJECTS) $(TESTOBJ) $(GTESTLIB)
	$(CC) $(CFLAGS) $(INC) $(TESTOBJ) -o $(TESTER) $(LIB) $(TESTLIB)

# Build Google Test library
$(GTESTLIB):
	(cd gtest && ./configure && make)

# Run tests
test: tester
	LD_LIBRARY_PATH=gtest/lib/.libs DYLD_LIBRARY_PATH=gtest/lib/.libs ./tester

.PHONY: clean

