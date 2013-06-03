IDIR =./include
CC=cc
CFLAGS=-I$(IDIR)
LDFLAGS=
EXECUTABLE=endian

ODIR=./obj
LDIR=./lib
SDIR=./src

LIBS=-lm

_DEPS = endian.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_SRCS=endian.c
_OBJ=$(_SRCS:.c=.o)

SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all: $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC)  $(LDFLAGS) $(OBJ) -o $@

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) *~ core $(IDIR)/*~











