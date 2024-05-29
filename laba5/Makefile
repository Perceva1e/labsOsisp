CC = gcc
CFLAGS = -Wall -pthread
TARGETS = message_queue message_queue_sem

SRCS = lab5-1.c lab5-2.c
OBJS = $(SRCS:.c=.o)

all: $(TARGETS)

message_queue: lab5-1.o
	$(CC) $(CFLAGS) -o $@ $^

message_queue_sem: lab5-2.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGETS)
