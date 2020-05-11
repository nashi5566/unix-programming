CC= gcc
CFLAG= -O3 -g -Wall -I include
OBJ= src/main.c

SHARED= src/sandbox.c

EXEC= ./sandbox
LIB= sandbox.so

all: $(EXEC) $(LIB)

run: $(EXEC) $(LIB)
		$(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@ -ldl

$(LIB): $(SHARED)
	$(CC) -fPIC -shared -o $@ $(SHARED) -I include -ldl

src/%.o: src/%.c
	$(CC) $(CCFLAG) -o $@ -c $<

clean:
	rm sandbox.so sandbox
