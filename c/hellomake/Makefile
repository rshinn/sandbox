IDIR =./include
CC=cc
CFLAGS=-I$(IDIR)
#CFLAGS=-I$(IDIR) -c -Wall
LDFLAGS=
EXECUTABLE=hellomake

ODIR=./obj
LDIR=./lib
SDIR=./src

LIBS=-lm

_DEPS = hellomake.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_SRCS=hellomake.c \
	  hellofunc.c

#$(info _SRCS = $(_SRCS))

_OBJ=$(_SRCS:.c=.o)
#_OBJ=$(patsubst %.c,%.o,$(_SRCS_))
#$(info _OBJ = $(_OBJ))

SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))
#$(info SRCS = $(SRCS))

#_OBJ = hellomake.o hellofunc.o
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
#$(info OBJ = $(OBJ))

all: $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC)  $(LDFLAGS) $(OBJ) -o $@
	#$(CC)  -o $@ $^ $(CFLAGS) $(LIBS)

#$(ODIR)/%.o: %.c $(DEPS)
#$(OBJ): $(SRCS)
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(OBJ) *~ core $(IDIR)/*~
	#rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~











