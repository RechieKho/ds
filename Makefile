# -- Makefile --

CC=gcc
CFLAGS=-Wextra -Wall -std=c11 -g

SRCDIR=src
OBJDIR=obj
BINDIR=bin
SRC=$(wildcard $(SRCDIR)/*.c)
OBJS=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
BIN=$(BINDIR)/main

DPNDIR=dpn
DPN=$(patsubst $(SRCDIR)/%.c, $(DPNDIR)/D-%, $(SRC))

all: setup $(BIN)

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
$(DPNDIR)/D-%: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -MT '$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<)' -MM $< > $@
	echo '	$(CC) $(CFLAGS) -c $< -o $$@' >> $@

include $(DPN)

# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean
release: $(BIN)

clean: 
	rm -rf $(BINDIR)/* $(OBJDIR)/* $(DPNDIR)/*


