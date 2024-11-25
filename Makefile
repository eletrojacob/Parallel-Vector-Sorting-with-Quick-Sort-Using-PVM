# Paths and compiler flags
PVM_ROOT = /path/to/pvm3  # Update this with the actual PVM installation path
PVM_ARCH = $(shell $(PVM_ROOT)/lib/pvmgetarch)
PVM_LIB = $(PVM_ROOT)/lib/$(PVM_ARCH)
PVM_INCLUDE = $(PVM_ROOT)/include

CC = gcc
CFLAGS = -g -I$(PVM_INCLUDE)
LDFLAGS = -L$(PVM_LIB) -lpvm3

# Targets
TARGETS = ordena quick

# Rules
all: $(TARGETS)

ordena: ordena.c
	$(CC) $(CFLAGS) -o ordena ordena.c $(LDFLAGS)

quick: quick.c
	$(CC) $(CFLAGS) -o quick quick.c $(LDFLAGS)

clean:
	rm -f $(TARGETS) *.o
