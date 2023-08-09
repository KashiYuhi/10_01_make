OBJS = main.o myfunc.o

main: $(OBJS)
	gcc $(OBJS) -o main $(LDFLAGS)

INCLUDE := -I/mnt/myfunc.h

CFLAGS := $(INCLUDE) $(CFLAGS)

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

.PHONY: all clean
all: main
clean:
	rm -f main $(OBJS)
