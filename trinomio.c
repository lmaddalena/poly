#include "trinomio.h"
#include <stdlib.h>		// malloc, free

//
// costruttore
//
t_trinomio *trinomio_ctor(double a, double b, double c) {

	t_monomio *mon_a = monomio_ctor();
	mon_a->coefficiente = a;
	mon_a->grado = 2;

	t_monomio *mon_b = monomio_ctor();
	mon_b->coefficiente = b;
	mon_b->grado = 1;

	t_monomio *mon_c = monomio_ctor();
	mon_c->coefficiente = c;
	mon_c->grado = 0;

	t_trinomio *tri = (t_trinomio*)malloc(sizeof(t_trinomio));

	tri->a = mon_a;
	tri->b = mon_b;
	tri->c = mon_c;

	return tri;
}

//
// distruttore
//
void trinomio_dtor(t_trinomio *t) {

	monomio_dtor(t->a);
	monomio_dtor(t->b);
	monomio_dtor(t->c);
	free(t);

}
