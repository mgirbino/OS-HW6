#Michael Girbino
#EECS 338 HW6: Baboon Crossing Semaphore Implementation
CC = gcc
CFLAGS = -std=c11 -ggdb
OUT = baboon_crossing.o
SRC = baboon_crossing.c

all:	processes

processes:
	$(CC) -o $(OUT) $(SRC) $(CFLAGS)  
	chmod 755 $(OUT)

clean:
	rm -f $(OUT)
