# lift life
# http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/makefile.4
CC=gcc
CFLAGS=-I. -I./mongoose -I./pool -DTHPOOL_DEBUG -pthread
OBJDIR = build
DEPS= parser.h server.h test-lib.h core.h graph.h graph.test.h pool/thpool.h hash-table.h hash-table.test.h cjson/cJSON.h cjson/cJSON_Utils.h
OBJ = parser.o server.o test-lib.o core.o graph.o graph.test.o pool/thpool.o hash-table.o hash-table.test.o cjson/cJSON.o cjson/cJSON_Utils.o
MAIN_OBJ = main.o
TEST_OBJ = core.test.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ) $(MAIN_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cnaked-test-bin: $(OBJ) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: test
test:
	make cnaked-test-bin && ./cnaked-test-bin

.PHONY: clean
clean:
	rm -rf *.o

