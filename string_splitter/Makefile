CC=gcc
CFLAGS=-I.
DEPS = string_splitter.h
OBJ = string_splitter.o test.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o test
