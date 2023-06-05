CC = gcc
CFLAGS = -pthread
TARGET = ex3.out

SOURCES = BoundedQueue.c UnboundedQueue.c main.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = BoundedQueue.h UnboundedQueue.h

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJECTS) $(TARGET)
