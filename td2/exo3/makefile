# utilisez `mingw32-make` à la place de `make` sous windows
main: ../exo1/*.o
	gcc -o $@ $^

%.o: %.c %.h
	gcc -c $<