#ifndef MONOMIO_H
#define MONOMIO_H

// t_monomio
typedef struct monomio {
	double coefficiente;
	int grado;
} t_monomio;

// t_monomiolistitem
typedef struct monlistitem {
	t_monomio *monomio;
	struct monlistitem *next;
} t_monomiolistitem;

// t_monomiolist
typedef struct monomiolist {
	t_monomiolistitem *item;
	t_monomiolistitem *__iterator;
} t_monomiolist;

t_monomio *monomio_ctor(void);
void monomio_dtor(t_monomio *);
int monomio_equals(t_monomio *, t_monomio *);
t_monomio *monomio_somma(t_monomio *, t_monomio *);
t_monomio *monomio_sottrai(t_monomio *, t_monomio *);
t_monomio *monomio_moltiplica(t_monomio *, t_monomio *);
t_monomio *monomio_dividi(t_monomio *, t_monomio *);
t_monomio *monomio_parse(char *);
char *monomio_tostring(t_monomio *mon);

t_monomiolist *monomiolist_ctor(void);
void monomiolist_dtor(t_monomiolist *);
void monomiolist_add(t_monomiolist *, t_monomio *);
t_monomio *monomiolist_getnext(t_monomiolist *list);

#endif