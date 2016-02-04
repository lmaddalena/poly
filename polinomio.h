#ifndef POLINOMIO_H
#define POLINOMIO_H

#include <stdlib.h>
#include "monomio.h"

// t_polinomio
typedef struct polinomio {
	t_monomiolist *list;
} t_polinomio;

// t_polinomiolistitem
typedef struct pollistitem {
	t_polinomio *polinomio;
	struct pollistitem *next;
} t_polinomiolistitem;

// t_polinomiolist
typedef struct polinomiolist {
	t_polinomiolistitem *item;
	t_polinomiolistitem *__iterator;
} t_polinomiolist;


t_polinomio *polinomio_ctor(void);
void polinomio_dtor(t_polinomio *);
char *polinomio_tostring(t_polinomio *);
int polinomio_getgrado(t_polinomio *);
t_polinomio *polinomio_normalizza(t_polinomio *);
t_polinomio *polinomio_somma(t_polinomio *, t_polinomio *);
t_polinomio *polinomio_sottrai(t_polinomio *, t_polinomio *);
t_polinomio *polinomio_moltiplica(t_polinomio *, t_polinomio *);
t_polinomiolist *polinomio_dividi(t_polinomio *, t_polinomio *);
double polinomio_valuta(t_polinomio *, double);
t_polinomio *polinomio_creatrinomio(double a, double b, double c);
void polinomio_radicitrinomio(double a, double b, double c, double radici[2], int *flgx1, int *flgx2);

t_polinomiolist *polinomiolist_ctor(void);
void polinomiolist_dtor(t_polinomiolist *list);
void polinomiolist_add(t_polinomiolist *list, t_polinomio *polinomio);
t_polinomio *polinomiolist_getnext(t_polinomiolist *list);
size_t polinomiolist_getsize(t_polinomiolist *list);
t_polinomio *polinomiolist_getelementat(t_polinomiolist *, int);

#endif