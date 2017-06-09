CC = gcc
INCLUDES = -I ./

all:
	$(CC) $(INCLUDES) mbntool.c -o mbntool

clean:
	rm mbntool
