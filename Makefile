CC		= gcc
CFLAGS		= -Wall -std=c99 -pedantic -Werror
LDFLAGS		= -Ofast -ggdb3
LDLIBS		= -lm -lmvec -lgsl -lcblas

SRCDIR		= src

SRC		= $(SRCDIR)/get_args.c \
		  $(SRCDIR)/read_file.c \
		  $(SRCDIR)/fit.c \
		  $(SRCDIR)/main.c \
		  $(SRCDIR)/norrish.c

DEPS		= $(SRCDIR)/definitions_and_headers.h
EXECUTABLE	= FitWaterActivity

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(SRC) -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)

