# -- Makefile --

CC=gcc
CFLAGS=-Wextra -Wall -std=c11 -g

SRCDIR=src
OBJDIR=obj
BINDIR=bin
LIBDIR=lib
SRC=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
BIN=$(BINDIR)/main
INCLUDE_LIB_DIR=$(LIBDIR)/include
LINUX_SO_LIB=$(LIBDIR)/libds.so
LINUX_A_LIB=$(LIBDIR)/libds.a


DPNDIR=dpn
DPN_o=$(patsubst $(SRCDIR)/%.c, $(DPNDIR)/D-%.o, $(SRC))

# user's command
test: setup $(BIN)

# optimized test (with -O flag)
Otest: CFLAGS=-Wall -O2 -DNDEBUG
Otest: test

shared: setup $(LINUX_SO_LIB) $(INCLUDE_LIB_DIR)

archive: setup $(LINUX_A_LIB) $(INCLUDE_LIB_DIR)

# setup
setup: $(DPNDIR) $(OBJDIR) $(OBJDIR)

$(DPNDIR): 
	mkdir $(DPNDIR)

$(BINDIR): 
	mkdir $(BINDIR)

$(OBJDIR): 
	mkdir $(OBJDIR)

# make binary from object
$(BIN):  $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# get dependency and generate recipe for obj
$(DPNDIR)/D-%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MT '$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<)' -MM $< > $@
	echo '	$(CC) $(CFLAGS) -c $< -o $$@' >> $@

include $(DPN_o)

# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean

# Compile to LIBs
$(LINUX_SO_LIB): GP.h HashTable.c HashTable.h LinkedList.c LinkedList.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ HashTable.c LinkedList.c 

$(LINUX_A_LIB): HashTable.o LinkedList.o
	ar rcs $(LINUX_A_LIB) HashTable.o LinkedList.o
# r - replace archive; c - create archive; s - index;

$(INCLUDE_LIB_DIR): 
	cp src/*.h lib/

clean: 
	rm -rf $(BINDIR)/* $(OBJDIR)/* $(DPNDIR)/*


