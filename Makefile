# Author: Tongxin Chen                                                
# UWNetID: tongxc                               
# Homework5 Makefile                   
# May 12, 2023
#
# Makefile for the tnine.c, trie.c, and trienode.h program.

# The compiler: gcc for C programs
CC = gcc

# Compiler flags:
# -Wall for debugger warnings
# -std=c11 for updated standards
CFLAGS = -Wall -std=c11
ifdef DEBUG
	CFLAGS += -g
endif

# The name of the program that we are producing.
TARGET = t9

# The "phony" target
all: $(TARGET)

# All the .o files we need for our executable.
OBJS = tnine.o trie.o

# The executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o t9 $(OBJS)

# An option for making a debug target
debug: CFLAGS += -g
debug: $(TARGET)

# Individual source files
tnine.o: tnine.c trienode.h
	$(CC) $(CFLAGS) -c tnine.c

trie.o: trie.c trienode.h
	$(CC) $(CFLAGS) -c trie.c

# A "phony" target to remove built files and backups
clean:
	rm -f *.o t9 *~
