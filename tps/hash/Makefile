all:
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o pruebas *.c
mem:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
clean:
	rm *.o pruebas
comp:
	gcc -g -o pruebas *.c
zip:
	zip hash *.c *.h
cleanzip:
	rm hash.zip