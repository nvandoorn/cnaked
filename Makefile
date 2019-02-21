CC=gcc
CFLAGS=-I.
DEPS= parser.h server.h test-lib.h core.h
OBJ = parser.o server.o test-lib.o core.o
MAIN_OBJ = main.o
TEST_OBJ = core.test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: $(OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS) && echo "\n\nRunning Tests\n\n" &&./test

.PHONY: clean
clean:
	rm -rf *.o

