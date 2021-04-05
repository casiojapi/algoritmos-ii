all:
	gcc -g -Wall -Wconversion -Wno-sign-conversion -o test *.c
mem:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./test
clean:
	rm *.o test
comp:
	gcc -g -o test *.c
zip:
	zip tp2 *.c *.h *.mk
cleanzip:
	rm tp2.zip