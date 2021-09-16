PEDANTIC_PARANOID_FREAK =       -g -O0 -Wall -Wshadow -Wcast-align \
				-Waggregate-return -Wstrict-prototypes \
				-Wredundant-decls -Wnested-externs \
				-Wpointer-arith -Wwrite-strings -finline-functions -Werror
CC = gcc
CPPFLAGS = -DDEBUG
LDFLAGS = -g -lm

include Makefile.config

ifdef FILTER_SIZE
CONFIG_FLAGS += -DFILTER_SIZ=$(FILTER_SIZE)
endif

CFLAGS = -g $(PEDANTIC_PARANOID_FREAK) $(CONFIG_FLAGS)

PROG = main

all : $(PROG)

main : main.o imgoper.o convol.o filter.o filutils.o hist.o matrix.o median.o pgmfil.o

clean :
	@rm -f $(PROG) *.o

cleanall : clean
	@rm -f $(PROG)