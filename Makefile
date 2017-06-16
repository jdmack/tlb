CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
#TESTDIR := tests
BUILDDIR := build
TARGET := tlb
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
TESTS   := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJ := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TESTS:.$(SRCEXT)=.o)) $(filter-out build/main.o,$(OBJECTS))

CFLAGS := -g -O0 -std=c++0x #-Wall
LIB := -lSDL2 -lSDL2_image -lSDL2_ttf -lGLEW -lGLU -lGL -static-libgcc -lMagick++

# Uncomment on CentOS 6 (GCC 4.4)
#CFLAGS += -Dnullptr='(NULL)'

INC := -I include -I lib -I /usr/include/ImageMagick/

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/gfx
	@mkdir -p $(BUILDDIR)/gfx/lighting
	@mkdir -p $(BUILDDIR)/util
	@mkdir -p $(BUILDDIR)/math
	@mkdir -p $(BUILDDIR)/action
	@mkdir -p $(BUILDDIR)/aiState
	@mkdir -p $(BUILDDIR)/ui
	@mkdir -p $(BUILDDIR)/event
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET) $(TESTER)"; $(RM) -r $(BUILDDIR) $(TARGET) $(TESTER)

.PHONY: clean

