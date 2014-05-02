CC     = gcc
FLAGS  = -Wall 
SRC    = hash.c test.c
OBJS   = $(SRC:.c=.o)
TARGET = test

all:$(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^

.PHONY:clean
clean:
	rm -f $(TARGET) $(OBJS)

