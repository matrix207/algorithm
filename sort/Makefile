# Create by Dennis 2014-05-06
CC     = gcc
FLAGS  = -Wall
SRC    = test.c heap_sort.c quick_sort.c
OBJS   = $(SRC:.c=.o)
# link math library for sqrt
LIBS   = -lm
TARGET = test

# Using condition compile for debug: make DEBUG=1
ifeq ($(DEBUG), 1) 
FLAGS += -g
endif

all:$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(FLAGS) $(LIBS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(FLAGS) -c $^

.PHONY:
clean:
	rm -f $(TARGET) $(OBJS)

