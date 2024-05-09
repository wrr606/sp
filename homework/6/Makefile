CC = gcc
CFLAGS = -Wall -std=gnu99
TARGET = server client
all: $(TARGET)

server: server.c net.c vector.c
	$(CC) $(CFLAGS) $^ -o $@

client: client.c net.c vector.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) *.exe
	$(MAKE) all