# -- Makefile --

# -- variable --
CC=gcc
CFLAGS=-Wextra -Wall -std=c11 -g
## DIR ##
SRCDIR:=src
OBJDIR:=obj
BINDIR:=bin
LIBDIR:=lib
DEPDIR:=dep
INCLUDE:=$(LIBDIR)/include
## FILES ##
SRCS:=$(wildcard $(SRCDIR)/*.c)
OBJS:=$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BIN:=$(BINDIR)/main
LINUX_SO_LIB:=$(LIBDIR)/libds.so
LINUX_A_LIB:=$(LIBDIR)/libds.a

OBJDEP:=$(patsubst $(OBJDIR)/%.o, $(DEPDIR)/a-%.o.d, $(OBJS))

# -- user's command --
test: pre $(BIN)
Otest: pre release $(BIN)
shared: pre release $(LINUX_SO_LIB) cp_headers
archive: pre release $(LINUX_A_LIB) cp_headers
depend: pre rm_depend $(OBJDEP)

# -- pre & post --
pre: setup_dir

# -- mode --
# release
release: CFLAGS=-Wall -O2 -DNDEBUG
release: clean

# -- procedure --
setup_dir: $(OBJDIR) $(BINDIR) $(LIBDIR) $(INCLUDE)

cp_headers: 
	cp $(SRCDIR)/*.h $(INCLUDE)

rm_depend:
	rm $(DEPDIR)/* -rf

clean: 
	rm -rf $(BINDIR)/* $(OBJDIR)/* $(LIBDIR)/*.so $(LIBDIR)/*.a $(INCLUDE)/*

clear: clean rm_depend

# -- make recipies --
## DIR ##
$(BINDIR): 
	mkdir $@

$(OBJDIR): 
	mkdir $@

$(LIBDIR): 
	mkdir $@

$(INCLUDE):
	mkdir $@

## BINARY ##
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

## LIBRARY ##
$(LINUX_SO_LIB): $(OBJS)
	$(CC) $(CFLAGS) $^ -fPIC -shared -o $@ 

$(LINUX_A_LIB): $(OBJS)
	ar rcs $@ $^
# r - replace archive; c - create archive; s - index;

## DEPENDENCY ##
$(DEPDIR)/a-%.o.d: $(SRCDIR)/%.c
	mkdir -p $(DEPDIR)
	gcc $< -MM -MF $@ -MT $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<)
	echo '	$(CC) $(CFLAGS) -c $< -o $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $<)' >> $@

# -- include --
include $(OBJDEP)
