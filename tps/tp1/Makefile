all: infix dc

infix:
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o infix calc_helper.c strutil.c infix.c pila.c cola.c -lm

dc:
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o dc calc_helper.c strutil.c dc.c pila.c cola.c -lm

mem:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas
clean:
	rm *.o pruebas dc infix *.txt
zip:
	zip tp1 *.c *.h *.mk