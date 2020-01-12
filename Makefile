CC = g++ -std=c++11
CFLAGS = -g -O2 -Wall -Wmissing-declarations -Weffc++ \
	-pedantic -pedantic-errors -Wextra -Wcast-align \
	-Wcast-qual -Wconversion -Wsign-conversion \
	-Wdisabled-optimization \
	-Werror -Wfloat-equal -Wformat=2 \
	-Wformat-nonliteral -Wformat-security \
	-Wformat-y2k \
	-Wimport -Winit-self -Winline \
	-Winvalid-pch \
	-Wlong-long \
	-Wmissing-field-initializers -Wmissing-format-attribute \
	-Wmissing-include-dirs -Wmissing-noreturn \
	-Wpacked -Wpointer-arith \
	-Wredundant-decls \
	-Wshadow -Wstack-protector \
	-Wstrict-aliasing=2 -Wswitch-default \
	-Wswitch-enum \
	-Wunreachable-code -Wunused \
	-Wunused-parameter \
	-Wvariadic-macros \
	-Wwrite-strings

PROG = exercise2
SRCDIR = src
LIBDIR = lib
BINDIR = bin
BUILDDIR = build
RESOURCESDIR = resources
CONFDIST := config/playercontrolsmapping.txt

IFLAGS = -I$(LIBDIR)/glad/include -I$(LIBDIR)/stb_image -Isrc
CFLAGS += $(IFLAGS)
LIBS = -lGL -lGLU -lglfw -ldl

DEP2D := $(shell find $(SRCDIR)/ $(LIBDIR)/ -type f -name '*.hpp' -o -name '*.h' | grep -v 3D)
SRC2D := $(shell find $(SRCDIR)/ -type f -name '*.cpp' -o -name '*.c' | grep -v 3D)
OBJ2D = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC2D))

DEP3D := $(shell find $(SRCDIR)/ $(LIBDIR)/ -type f -name '*.hpp' -o -name '*.h' | grep -v 2D)
SRC3D := $(shell find $(SRCDIR)/ -type f -name '*.cpp' -o -name '*.c' | grep -v 2D)
OBJ3D = $(patsubst %.cpp,$(BUILDDIR)/%.o,$(SRC3D))

# Local libs can be either *.c or *.cpp files. The object files will be: *.c.o
# or *.cpp.o
LIBSRC := $(shell find $(LIBDIR)/ -type f -name '*.cpp' -o -name '*.c')
LIBOBJ = $(patsubst %,$(BUILDDIR)/%.o,$(LIBSRC))

ifeq ($(3D), 1)
	CFLAGS += -DMODE_3D
	DEP := $(DEP3D)
	SRC := $(SRC3D)
	OBJ := $(OBJ3D)
else
	DEP := $(DEP2D)
	SRC := $(SRC2D)
	OBJ := $(OBJ2D)
endif

all: prepare $(PROG)

$(BUILDDIR)/$(SRCDIR)/%.o: $(SRCDIR)/%.cpp $(DEP)
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILDDIR)/$(LIBDIR)/%.o: $(LIBDIR)/%
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(IFLAGS)

$(PROG): $(OBJ) $(LIBOBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS)

prepare:
	@mkdir -p $(BUILDDIR) $(BINDIR) $(RESOURCESDIR)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)
