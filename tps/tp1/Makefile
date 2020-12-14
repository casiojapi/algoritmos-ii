all: strutil

strutil: strutil.c strutil.o
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o strutil strutil.c -lm

infix:
	gcc -g -Wall -Wconversion -Wno-sign-conversion -Werror -o infix calc_helper.c strutil.c infix.c pila.c cola.c -lm

dc:
	gcc -g -g -Wall -Werror -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wno-conversion -o dc calc_helper.c strutil.c dc.c pila.c cola.c -lm

mem:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./infix
clean:
	rm *.o pruebas dc infix strutil *.zip strutil
zip:
	zip tp1 *.c *.h *.mk

cast: 
	gcc -g -Wall -Werror -pedantic -Wformat=2 -Wshadow -Wpointer-arith -Wunreachable-code -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wno-conversion -o dc.c dc





