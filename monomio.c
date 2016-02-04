#include "monomio.h"
#include <stdio.h>	
#include <stdlib.h>		// malloc, free
#include <string.h>		// strcpy, strcat
#include <math.h>		// abs

//
// costruttore
//
t_monomio *monomio_ctor(void) {
	t_monomio *mon = (t_monomio*) malloc(sizeof(t_monomio));
	mon->grado = 0;
	mon->coefficiente = 0;
	return mon;
}

//
// distruttore
//
void monomio_dtor(t_monomio *monomio) {
	free(monomio);
}

//
// determina se due monomi sono uguali
//
int monomio_equals(t_monomio *mon1, t_monomio *mon2) {

	if (mon1->grado == mon2->grado && mon1->coefficiente == mon2->coefficiente)
		return 1;
	else
		return 0;
}

//
// somma due monomi
//
t_monomio *monomio_somma(t_monomio *mon1, t_monomio *mon2){

	if (mon1->grado != mon2->grado)
	{
		// i monomi non sono simili
		return NULL;
	}
	else
	{
		t_monomio *mon = monomio_ctor();
		mon->grado = mon1->grado;
		mon->coefficiente = mon1->coefficiente + mon2->coefficiente;
		return mon;
	}
}

//
// sottrae due monomi
//
t_monomio *monomio_sottrai(t_monomio *mon1, t_monomio *mon2){

	if (mon1->grado != mon2->grado)
	{
		// i monomi non sono simili
		return NULL;
	}
	else
	{
		t_monomio *mon = monomio_ctor();
		mon->grado = mon1->grado;
		mon->coefficiente = mon1->coefficiente - mon2->coefficiente;
		return mon;
	}
}

//
// moltiplica due monomi
//
t_monomio *monomio_moltiplica(t_monomio *mon1, t_monomio *mon2){

	t_monomio *mon = monomio_ctor();
	mon->grado = mon1->grado + mon2->grado;
	mon->coefficiente = mon1->coefficiente * mon2->coefficiente;
	return mon;
}

//
// divide due monomi
//
t_monomio *monomio_dividi(t_monomio *mon1, t_monomio *mon2){

	t_monomio *mon = monomio_ctor();
	mon->grado = mon1->grado - mon2->grado;
	mon->coefficiente = mon1->coefficiente / mon2->coefficiente;
	return mon;
}

//
// to string
//
char *monomio_tostring(t_monomio *mon){

	char *s = (char *)malloc(30);

	// segno
	if (mon->coefficiente < 0)
		strcpy(s, "-");
	else
		strcpy(s, "+");

	// coefficiente
	double c = abs(mon->coefficiente);
	if (c != 1 || mon->grado == 0)
	{
		char coeff[20];

		if ((int)c == c)
			sprintf(coeff, "%i", (int)c);		// numero inter
		else
			sprintf(coeff, "%f", c);			// numero decimale


		strcat(s, coeff);
	}

	//grado
	int g = abs(mon->grado);
	char grado[20];
	itoa(g, grado, 10);
	if (g > 1)
	{
		strcat(s, "x^");
		strcat(s, grado);
	}
	else if (g == 1)
	{
		strcat(s, "x");
	}

	return s;

}


//
// converte la stringa in un monomio
//
t_monomio *monomio_parse(char *s){

	int segno = 1;			// segno del monomio
	int grado = 1;			// grado del monomio
	double coeff = 1.0;		// coefficiente del monomio
	int idx = -1;			// indice della parte letterale nella stringa

	char *p;
	
	if (s == NULL || s[0] == '\0' || s[0] == '\n')
		return NULL;

	// segno
	if (s[0] == '-')
	{
		segno = -1;
		s++;			// toglie il segno
	}
	else if (s[0] == '+')
	{
		segno = 1;		// toglie il segno
		s++;
	}

	// cerca la x o la X
	p = strchr(s, 'x');
	if (p == NULL) 
		p = strchr(s, 'X');

	// calcola l'indice della x
	if (p != NULL)
		idx = p - s;
	
	// coefficiente
	if (idx == 0)
	{
		coeff = 1.0 * segno;
		grado = 1;
	}
	else if (idx > 0)
	{
		char sc[10]; 
		strncpy(sc, s, idx);
		sc[idx] = '\0';
		coeff = atof(sc) * segno;
		grado = 1;
	}
	else
	{
		coeff = atof(s) * segno;
		grado = 0;
	}

	// grado

	// cerca il simbolo ^
	p = strchr(s, '^');

	if (p != NULL)
	{
		char sg[10];
		strcpy(sg, ++p);
		grado = atoi(sg);
	}


	t_monomio *mon = monomio_ctor();
	mon->grado = grado;
	mon->coefficiente = coeff;
	return mon;
}

//
// costruttore
//
t_monomiolist *monomiolist_ctor(void){
	t_monomiolist *list = (t_monomiolist*)malloc(sizeof(t_monomiolist));
	list->item = NULL;
	list->__iterator = NULL;
	return list;
}

//
// distruttore
//
void monomiolist_dtor(t_monomiolist *list) {

	t_monomiolistitem *p, *q;
	for (p = list->item; p != NULL; p = q){
		q = p->next;
		free(p);
	}

	free(list);

}

//
// aggiunge un monomio alla lista
//
void monomiolist_add(t_monomiolist *list, t_monomio *monomio)
{
	if (list == NULL || monomio == NULL)
		return;

	// crea l'elemento della lista
	t_monomiolistitem *item = (t_monomiolistitem*)malloc(sizeof(t_monomiolistitem));
	item->monomio = monomio;
	item->next = NULL;


	if (list->item == NULL)
	{
		list->item = item;
	}
	else
	{
		t_monomiolistitem *last = NULL;

		// si posiziona alla fine
		for (last = list->item; last->next != NULL; last = last->next)
			;

		// aggiunge l'elemento alla lista
		last->next = item;
	}


};

//
// restituisce il prossimo monomio nella lista
//
t_monomio *monomiolist_getnext(t_monomiolist *list){
	if (list == NULL || list->item == NULL)
		return NULL;
	else
	{
		if (list->__iterator == NULL)
			list->__iterator = list->item;
		else
			list->__iterator = list->__iterator->next;

		if (list->__iterator != NULL)
			return list->__iterator->monomio;
		else
			return NULL;

	}
}

