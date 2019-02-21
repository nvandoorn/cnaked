CC=gcc
CFLAGS=-I.
DEPS= parser.h server.h test-lib.h main.h
OBJ = parser.o server.o test-lib.o main.o
MAIN_OBJ = 
TEST_OBJ = main.test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o

