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

CFLAGS += -Iglad/include
LIBS = -lGL -lGLU -lglfw -ldl

PROG = exercise1
SRCDIR = src
BINDIR = bin
BUILDDIR = build
CONFDIST := config/playercontrolsmapping.txt

DEP := $(shell find $(SRCDIR)/ glad/include/ -type f -name '*.hpp' -o -name '*.h')
SRC := $(shell find $(SRCDIR)/ glad/src/ -type f -name '*.cpp' -o -name '*.c')
OBJ = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRC))

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(DEP)
	@mkdir -p $(shell dirname $@)
	$(CC) -c -o $@ $< $(CFLAGS)

all: prepare $(PROG)

$(PROG): $(OBJ)
	$(CC) -o $(BINDIR)/$@ $^ $(CFLAGS) $(LIBS)

prepare:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)

clean:
	rm -rf $(BUILDDIR) $(BINDIR)
