CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c mpu6050.c nRF24L01.c gpio_config.c
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
