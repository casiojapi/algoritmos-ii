all:
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas calc_helper.c strutil.c dc.c pila.c -lm
mem:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
clean:
	rm *.o pruebas
zip:
	zip tp1 *.c *.h