#ifndef TRINOMIO_H
#define TRINOMIO_H

#include "monomio.h"

// t_trinomio
typedef struct trinomio {
	t_monomio *a;
	t_monomio *b;
	t_monomio *c;
} t_trinomio;


t_trinomio *trinomio_ctor(double a, double b, double c);
void trinomio_dtor(t_trinomio *);

#endif