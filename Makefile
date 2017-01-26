CC=gcc
CFLAGS= -fPIC -Werror -Wextra -Wall -pedantic -g3 -std=c99 -Iinclude -fvisibility=hidden
        
LDFLAGS= -shared
SRC=src/calloc.c src/free.c src/funclib.c src/malloc.c src/meta_functions.c src/realloc.c src/unit.c
OBJ=$(SRC:.c=.o)
LIB=libmalloc.so
TARGET=malloc

all: $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET)
#	LD_LIBRARY_PATH=libmalloc.so ./malloc

lib: $(LIB)

$(LIB): 
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(LIB)

clean:
	$(RM) $(OBJ) $(LIB) $(TARGET)

check:
	LD_LIBRARY_PATH=libmalloc.so ./malloc
