FLAGS := -std=c99 -I./inc/ -fPIC -Wall -Werror -Wpedantic -Wextra -c -g -o

all: lib_lfrecord_vector.so

lib_lfrecord_vector.so: out/vector.o
	gcc -shared -o $@ $^


out/vector.o: src/vector.c
	gcc $(FLAGS) $@ $^

.PHONY: clean

clean:
	rm *.so *.exe out/*.o

