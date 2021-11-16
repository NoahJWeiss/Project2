make:
	gcc -pthread -Wall -o imath imath.c

memcheck:
	valgrind ./imath ./photos/cayuga_1.ppm

clean:
	rm -f imath
