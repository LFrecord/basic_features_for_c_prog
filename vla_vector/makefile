FLAGS := -std=c99 -I./inc/ -fPIC -Wall -Werror -Wpedantic -Wextra -c -g -o

all: lib_lfrecord_vector.so unit_tests.exe

lib_lfrecord_vector.so: out/vector.o
	gcc -shared -o $@ $^

unit_tests.exe: out/check_unit_tests.o out/check_vector.o out/vector.o
	gcc -o $@ $^ -lcheck

out/check_unit_tests.o: unit_tests/check_unit_tests.c
	gcc $(FLAGS) $@ $^

out/check_vector.o: unit_tests/check_vector.c
	gcc $(FLAGS) $@ $^

out/vector.o: src/vector.c
	gcc $(FLAGS) $@ $^

.PHONY: clean

clean:
	rm *.so *.exe out/*.o

