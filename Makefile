CC		= gcc
CFLAGS		= -Wall -std=c18 -pedantic -Werror
LDFLAGS		= -Ofast -ggdb3
LDLIBS		= -lm -lmvec -lgsl -lcblas

SRCDIR		= src
MODELSDIR	= src/models
BINDIR		= bin

SRC		= $(SRCDIR)/get_args.c \
		  $(SRCDIR)/read_file.c \
		  $(SRCDIR)/fit.c \
		  $(SRCDIR)/main.c \
		  $(MODELSDIR)/norrish.c \
		  $(MODELSDIR)/virial.c

DEPS		= $(SRCDIR)/definitions_and_headers.h
EXECUTABLE	= $(BINDIR)/FitWaterActivity
SYS_FILE	= /usr/bin/FitWaterActivity

.PHONY: all clean install
all: $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

install: $(EXECUTABLE)
	cp $(EXECUTABLE) $(SYS_FILE)

uninstall: $(SYS_FILE)
	rm -f $(SYS_FILE)

$(EXECUTABLE): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(SRC) -o $@

