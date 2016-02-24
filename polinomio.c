#include "polinomio.h"
#include <stdlib.h>		// malloc, free
#include <string.h>		// strlen
#include <math.h>		// pow, sqrt

// costruttore polinomio
t_polinomio *polinomio_ctor(void) {
	t_polinomio *pol = (t_polinomio*)malloc(sizeof(t_polinomio));
	pol->list = NULL;
	return pol;
}

// distruttore polinomio
void polinomio_dtor(t_polinomio *polinomio) {

	monomiolist_dtor(polinomio->list);
	free(polinomio);
}

// restituisce il polinomio in formato stringa
char *polinomio_tostring(t_polinomio *pol) {

	if (pol == NULL || pol->list == NULL)
		return NULL;

	t_monomio *item = NULL;
	int len = 0;

	// calcola la lunghezza
	while ((item = monomiolist_getnext(pol->list)) != NULL)
	{
		len += strlen(monomio_tostring(item));
	}

    // spazio per \0
    len++;
    
	// alloca
	char *s = (char*)malloc(len);

	// crea la stringa
	strcpy(s, "");
	while ((item = monomiolist_getnext(pol->list)) != NULL)
	{
		strcat(s, monomio_tostring(item));
	}

	return s;

}

//
// crea un trinomio di seconfo grado nella forma ax^2+bx+c
//
t_polinomio *polinomio_creatrinomio(double a, double b, double c) {

	t_monomio *mon_a = monomio_ctor();
	mon_a->coefficiente = a;
	mon_a->grado = 2;

	t_monomio *mon_b = monomio_ctor();
	mon_b->coefficiente = b;
	mon_b->grado = 1;

	t_monomio *mon_c = monomio_ctor();
	mon_c->coefficiente = c;
	mon_c->grado = 0;

	t_polinomio *pol = polinomio_ctor();
	pol->list = monomiolist_ctor();

	monomiolist_add(pol->list, mon_a);
	monomiolist_add(pol->list, mon_b);
	monomiolist_add(pol->list, mon_c);

	return pol;
}

//
// calcola le radici del trinomio di secondo grado
//
void polinomio_radicitrinomio(double a, double b, double c, double radici[2], int *flgx1, int *flgx2) {

	*flgx1 = 0;		// flag che cindica se è stato calcolato il valore della prima radice (x1)
	*flgx2 = 0;		// flag che cindica se è stato calcolato il valore della seconda radice (x1)

	if (a == 0)
	{
		double x1 = -c / b;
		radici[0] = x1;
		*flgx1 = 1;

		return;

	}
	else
	{
		// calcola il discriminante
		double d = (pow(b, 2) - 4 * a * c);

		// se il discriminante < 0 non ci sono soluzioni reali
		if (d < 0)
		{
			return;
		}

		// calcola le radici
		double x1 = (-b - sqrt(d)) / (2 * a);
		double x2 = (-b + sqrt(d)) / (2 * a);

		// restituisce il risultato
		radici[0] = x1;
		radici[1] = x2;
		*flgx1 = 1;
		*flgx2 = 1;

	}

}


//
// restituisce il grado del polinomio
//
int polinomio_getgrado(t_polinomio *pol) {

	int g = 0;

	t_monomio *item = NULL;

	// calcola la lunghezza
	while ((item = monomiolist_getnext(pol->list)) != NULL)
	{
		if (item->grado > g && item->coefficiente != 0) g = item->grado;
	}

	return g;
}

//
// normalizza il polinomio. Restituisce un nuovo polinomio
//
t_polinomio *polinomio_normalizza(t_polinomio *pol) {

	int g = 0;
	int i = 0;

	// grado del polinomio
	g = polinomio_getgrado(pol);

	// crea un nuovo polinomio
	t_polinomio *pol_norm = polinomio_ctor();

	// creo la nuova lista di monomi
	pol_norm->list = monomiolist_ctor();

	t_monomio *mon = NULL;

	for (i = 0; i <= g; i++) {
		
		int grado = g - i;
		int coeff = 0;

		// creo il nuovo monomio
		mon = monomio_ctor();
		mon->grado = grado;
		mon->coefficiente = coeff;

		// itero nei monomi del polinomio
		t_monomio *item = NULL;
		while ((item = monomiolist_getnext(pol->list)) != NULL)
		{
			if (item->grado == mon->grado) mon->coefficiente = mon->coefficiente + item->coefficiente;
		}
		pol_norm->list->__iterator = NULL;

		// se il coefficente � diverso da zero, aggiungo il monomio alla lista
		if (mon->coefficiente != 0)
			monomiolist_add(pol_norm->list, mon);
		else
			monomio_dtor(mon);
	}

	// se il polinomio � vuoto aggiungo zero
	if (pol_norm->list->item == NULL)
	{
		mon = monomio_ctor();
		mon->grado = 0;
		mon->coefficiente = 0;
		monomiolist_add(pol_norm->list, mon);
	}


	return pol_norm;

}

//
// somma due polinomi
//
t_polinomio *polinomio_somma(t_polinomio *pol1, t_polinomio *pol2) {

	// crea un nuovo polinomio
	t_polinomio *pol = polinomio_ctor();
	pol->list = monomiolist_ctor();

	t_monomio *item = NULL;

	// aggiunge i monomi del primo polinomio
	while ((item = monomiolist_getnext(pol1->list)) != NULL)
	{
		monomiolist_add(pol->list, item);
	}

	// aggiunge i monomi del desconto polinomio
	while ((item = monomiolist_getnext(pol2->list)) != NULL)
	{
		monomiolist_add(pol->list, item);
	}

	// normalizza il polinomio
	pol = polinomio_normalizza(pol);

	// restituisce il polinomio
	return pol;
}

//
// sottrae il polinomio2 dal polinomio1
//
t_polinomio *polinomio_sottrai(t_polinomio *pol1, t_polinomio *pol2) {

	// crea un nuovo polinomio
	t_polinomio *pol = polinomio_ctor();
	pol->list = monomiolist_ctor();

	t_monomio *item = NULL;

	// aggiunge i monomi del primo polinomio
	while ((item = monomiolist_getnext(pol1->list)) != NULL)
	{
		monomiolist_add(pol->list, item);
	}

	// aggiunge i monomi del secondo polinomio cambiati di segno
	while ((item = monomiolist_getnext(pol2->list)) != NULL)
	{
		t_monomio *mon = monomio_ctor();
		mon->grado = item->grado;
		mon->coefficiente = -(item->coefficiente);
		monomiolist_add(pol->list, mon);
	}

	// normalizza il polinomio
	pol = polinomio_normalizza(pol);

	// restituisce il polinomio
	return pol;

}

//
// moltiplica il polinomio1 con il polinomio2
//
t_polinomio *polinomio_moltiplica(t_polinomio *pol1, t_polinomio *pol2) {

	// creo un novo polinomio
	t_polinomio *pol = polinomio_ctor();
	pol->list = monomiolist_ctor();

	t_monomio *m = NULL;
	t_monomio *n = NULL;

	// pol1 e pol2 potrebbero puntare allo stesso polinomio,
	// in questo caso l'iterazione con getnext non funzionerebbe.
	// per ovviare copia i monomi di pol2 in una nuova lista
	t_monomiolist *templist = monomiolist_ctor();
	while ((n = monomiolist_getnext(pol2->list)) != NULL)
	{
		monomiolist_add(templist, n);
	}


	while ((m = monomiolist_getnext(pol1->list)) != NULL)
	{
		while ((n = monomiolist_getnext(templist)) != NULL)
		{
			monomiolist_add(pol->list, monomio_moltiplica(m, n));
		}
	}

	// normalizza il polinomio
	pol = polinomio_normalizza(pol);

	// restituisce il polinomio
	return pol;
}

//
// divide pol1 per il pol2. 
//
t_polinomiolist *polinomio_dividi(t_polinomio *pol1, t_polinomio *pol2) {

	t_polinomio *quoziente = NULL;
	t_polinomio *resto = NULL;

	// normalizza
	t_polinomio *dividendo = polinomio_normalizza(pol1);
	t_polinomio *divisore = polinomio_normalizza(pol2);

	if (polinomio_getgrado(divisore) > polinomio_getgrado(dividendo))
	{
		// divisore maggiore del dividendo
		quoziente = polinomio_ctor();
		quoziente->list = monomiolist_ctor();
		monomiolist_add(quoziente->list, monomio_parse("0"));

		resto = dividendo;
	}
	else
	{
		t_polinomio *r = dividendo;
		t_monomio *a;
		t_monomio *b;
		t_monomio *c;

		t_monomiolist *listaquozienti = monomiolist_ctor();



		while (polinomio_getgrado(r) >= polinomio_getgrado(divisore) && r->list->item->monomio->coefficiente != 0)
		{
			a = divisore->list->item->monomio; 	// monomio di grado pi� elevato
			b = r->list->item->monomio;			// monomio di grado pi� elevato
			c = monomio_dividi(b, a);			// divide

			
			monomiolist_add(listaquozienti, c);
			t_polinomio *m = polinomio_ctor();
			m->list = monomiolist_ctor();
			monomiolist_add(m->list, c);

			m = polinomio_moltiplica(m, divisore);
			r = polinomio_sottrai(r, m);
			r = polinomio_normalizza(r);
		}

		// quoziente
		quoziente = polinomio_ctor();
		quoziente->list = listaquozienti;

		// resto
		resto = r;

	}


	// lista dei risultati
	t_polinomiolist *res = polinomiolist_ctor();
	polinomiolist_add(res, quoziente);
	polinomiolist_add(res, resto);

	return res;
}

//
// valuta il polinomio
//
double polinomio_valuta(t_polinomio *pol, double d){

	double ret = 0;
	t_monomio *mon = NULL;

	while ((mon = monomiolist_getnext(pol->list)) != NULL)
	{
		ret += mon->coefficiente * pow(d, mon->grado);
	}

	return ret;
}

//
// costruttore polinomiolist
//
t_polinomiolist *polinomiolist_ctor(void){
	t_polinomiolist *list = (t_polinomiolist*)malloc(sizeof(t_polinomiolist));
	list->item = NULL;
	list->__iterator = NULL;
	return list;
}

//
// distruttore polinomiolist
//
void polinomiolist_dtor(t_polinomiolist *list) {

	t_polinomiolistitem *p, *q;
	for (p = list->item; p != NULL; p = q){
		q = p->next;
		free(p);
	}

	free(list);

}

//
// aggiunge un polinomio alla lista
//
void polinomiolist_add(t_polinomiolist *list, t_polinomio *polinomio)
{
	if (list == NULL || polinomio == NULL)
		return;

	// crea l'elemento della lista
	t_polinomiolistitem *item = (t_polinomiolistitem*)malloc(sizeof(t_polinomiolistitem));
	item->polinomio = polinomio;
	item->next = NULL;


	if (list->item == NULL)
	{
		list->item = item;
	}
	else
	{
		t_polinomiolistitem *last = NULL;

		// si posiziona alla fine
		for (last = list->item; last->next != NULL; last = last->next)
			;

		// aggiunge l'elemento alla lista
		last->next = item;
	}


};

//
// restituisce il prossimo polinomio nella lista
//
t_polinomio *polinomiolist_getnext(t_polinomiolist *list){
	if (list == NULL || list->item == NULL)
		return NULL;
	else
	{
		if (list->__iterator == NULL)
			list->__iterator = list->item;
		else
			list->__iterator = list->__iterator->next;

		if (list->__iterator != NULL)
			return list->__iterator->polinomio;
		else
			return NULL;

	}
}


//
// Restituisce l'elemento alla posizione specificata
//
t_polinomio *polinomiolist_getelementat(t_polinomiolist *list, int index)
{
	if (list == NULL || index < 0)
		return NULL;

	t_polinomio *pol = NULL;

	while (index-- >= 0)
		pol = polinomiolist_getnext(list);

	list->__iterator = NULL;

	return pol;
}

//
// restituisce il numero di elementi presenti nella lista
//
size_t polinomiolist_getsize(t_polinomiolist *list){

	t_polinomio *item = NULL;
	size_t c = 0;

	while ((item = polinomiolist_getnext(list)) != NULL)
	{
		c++;
	}

	return c;
}
