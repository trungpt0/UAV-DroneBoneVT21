CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c motor.c neo6mv2.c mpu9250.c
OBJS = $(SRCS:.c=.o)
TARGET = main

.PHONY = all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
