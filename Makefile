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
LINUX_SO_LIB=$(LIBDIR)/libds.so
LINUX_A_LIB=$(LIBDIR)/libds.a


DPNDIR=dpn
DPN_o=$(patsubst $(SRCDIR)/%.c, $(DPNDIR)/D-%.o, $(SRC))

# user's command
test: $(BIN)

# optimized test (with -O flag)
Otest: CFLAGS=-Wall -O2 -DNDEBUG
Otest: test

shared: $(LINUX_SO_LIB)

archive: $(LINUX_A_LIB) 

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
$(LINUX_SO_LIB): $(SRCDIR)/GP.h $(SRCDIR)/HashTable.c $(SRCDIR)/HashTable.h $(SRCDIR)/LinkedList.c $(SRCDIR)/LinkedList.h
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $(SRCDIR)/HashTable.c $(SRCDIR)/LinkedList.c 

$(LINUX_A_LIB): $(SRCDIR)/HashTable.o $(SRCDIR)/LinkedList.o
	ar rcs $(LINUX_A_LIB) $(SRCDIR)/HashTable.o $(SRCDIR)/LinkedList.o
# r - replace archive; c - create archive; s - index;

clean: 
	rm -rf $(BINDIR)/* $(OBJDIR)/* $(DPNDIR)/* $(LIBDIR)/*.so $(LIBDIR)/*.a 


