CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -pedantic -Iinclude -Werror -fvisibility=hidden -fPIC 
VPATH= src tests
LIBOBJS= meta_functions.o funclib.o malloc.o free.o calloc.o realloc.o
LDFLAGS=-shared
TESTFLAGS= -Wall -Wextra -std=c99 -pedantic -Iinclude
LIB=libmalloc.so
TEST=unit
TESTOBJS=unit.o

.PHONY : all check clean

all: $(LIB)
	$(RM) $(LIBOBJS)

$(LIB)!: CFLAGS += OBJSFLAGS
$(LIB): $(LIBOBJS)
	$(CC) $(LDFLAGS) -o $@  $^
	$(RM) $(LIBOBJS)

check:
	LD_LIBRARY_PATH=. ./$(TEST)
$(TEST):$(TESTOBJS)
	$(CC) $(TESTFLAGS) -o $@ $< -L. -lmalloc
	$(RM) $(TESTOBJS)

debug: CFLAGS+=-g
debug: TESTFLAGS+=-g
debug: $(LIB) $(TEST)

clean:
	$(RM) $(LIB) $(LIBOBJS) $(TEST) $(TESTOBJS)
