CC		= gcc
CFLAGS		= -Wall -std=c99 -pedantic -Werror
LDFLAGS		= -Ofast
LDLIBS		= -lm -lmvec -lgsl -lcblas

SRC		= read_file.c \
		  fit.c \
		  main.c

DEPS		= definitions_and_headers.h
EXECUTABLE	= FitWaterActivity

.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC) $(DEPS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) $(SRC) -o $@

.PHONY: clean
clean:
	rm -f $(EXECUTABLE)

