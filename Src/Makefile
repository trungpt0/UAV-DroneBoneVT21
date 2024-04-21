CC = gcc
CFLAGS = -Wall -Wextra

SRCS = main.c motor.c neo6mv2.c mpu6050.c
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
