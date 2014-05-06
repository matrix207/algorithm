# Create by Dennis 2014-05-06
CC     = gcc
FLAGS  = -Wall
SRC    = hash.c test.c
OBJS   = $(SRC:.c=.o)
# link math library for sqrt
LIBS   = -lm
TARGET = test

# Using for mtrace to debug: mtrace output
#FLAGS += -DMTRACE

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

