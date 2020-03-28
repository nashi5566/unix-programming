CC = gcc
CFLAGS = -O2 -g -Wall 
OBJ = \
		src/main.o\
		src/connect.o\
		src/list.o\
		src/proc.o

EXEC = hw1

src/%.o: src/%.c
	$(CC) $(CFLAG) -o $@ -c $<

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

LIBS =  -lc

all: $(EXEC)

run: $(EXEC)
	sudo ./$(EXEC)

.PHONY: clean
clean:
	rm *.o
