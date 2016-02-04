fibo: poly.o polinomio.o monomio.o
	gcc -std=c99 poly.o polinomio.o monomio.o -o poly

poly.o : ../poly.h ../poly.c
	gcc -std=c99 -c ../poly.c

polinomio.o : ../polinomio.c ../polinomio.h
	gcc -std=c99 -c ../polinomio.c

monomio.o : ../monomio.c ../monomio.h
	gcc -std=c99 -c ../monomio.c
