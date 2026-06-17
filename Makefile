# Makefile for data-structures


CC = gcc
CFLAGS = -Wall -c

OBJECTS = stack.o queue.o dynamic_array.o hash_table.o
LIB_NAME = libds.a

all: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	ar rcs $(LIB_NAME) $(OBJECTS)

stack.o: Stack/stack.c Stack/stack.h
	$(CC) $(CFLAGS) Stack/stack.c -o stack.o

queue.o: Queue/Queue.c Queue/Queue.h Stack/stack.h
	$(CC) $(CFLAGS) Queue/Queue.c -o queue.o

dynamic_array.o: Array/dynamic_array.c Array/dynamic_array.h
	$(CC) $(CFLAGS) Array/dynamic_array.c -o dynamic_array.o

hash_table.o: Hash_Table/hash_table.c hash_table/hash_table.h
	$(CC) $(CFLAGS) Hash_Table/hash_table.c -o hash_table.o

clean:
	rm -f *.o $(LIB_NAME)
