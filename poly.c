#include "monomio.h"
#include "polinomio.h"
#include "trinomio.h"
#include "poly.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

t_polinomiolist *polinomilist = NULL;

int main(int argc, char* argv[])
{
    polinomilist = polinomiolist_ctor();
    
	printf("\n");
	printf("PROGETTO PER L'ESAME DI LABORATORIO DI PROGRAMMAZIONE A.A. 2007/2008\n");
	printf("Gestione Polinomi\n");
	printf("by Luca Maddalena\n");

	for (;;)
	{
		printf("\n");
		printf("Menu principale:\n");
		printf("--------------------------------------------------------\n");
		printf("1. Inserimento polinomio\n");
		printf("2. Visualizza polinomi inseriti\n");
		printf("3. Svuota la lista dei polinomi inseriti\n");
		printf("4. Valuta Polinomi\n");
		printf("5. Operazioni sui Polinomi\n");
		printf("6. Inserisci e valuta un trinomio di 2^ grado\n");
		printf("7. Termina\n");
		printf("\n");

		// chiede di scegliere una opzione
		int i = 0;
		char s[16];
		fgets(s, 16, stdin);
		i = atoi(s);

		switch (i)
		{
		case 1:
			inspolinomio();
			break;

		case 2:
			visualizzapolinomi();
			break;

		case 3:
			svuotalistapolinomi();
			break;

		case 4:
			valutapolinomi();
			break;

		case 5:
			operazioni();
			break;

		case 6:
			instrinomio();
			break;

		case 7:
			printf("\nFine.");
			return 0;
		}

	}
	 
}

//
// inserimento polinomi
//
void inspolinomio(void){
	
	printf("\n");
	printf("Inserimento polinomio:\n");
	printf("----------------------\n");

	t_monomiolist *monomilist = monomiolist_ctor();

	char s[16];

	do {

		// richiede di inserire un monomio
		printf("Inserisci un monomio (esempio: 2x^3) oppure [INVIO] per terminare: ");
		fgets(s, 16, stdin);
	
		// parsing
		t_monomio *mon = monomio_parse(s);

		// aggiunge il monomio alla lista
		if (mon != NULL)
			monomiolist_add(monomilist, mon);

	} while (s[0] != '\n' && s[0] != '\0');

	if (monomilist->item != NULL){

		// crea il polinomio
		t_polinomio *pol = polinomio_ctor();
		pol->list = monomilist;

		// visualizza il polinomio inserito
		printf("\nHai inserito il seguente polinomio: %s\n", polinomio_tostring(pol));

		// chiede se accettare il polinomio
		if (domanda("Accetti il polinomio inserito?") == 1)
		{
			// normalizza il polinomio
			t_polinomio *pol_norm = polinomio_normalizza(pol);
			polinomio_dtor(pol);

			// inserisce il polinomio
			polinomiolist_add(polinomilist, pol_norm);
		}
		else {
			// distrugge il polinomio
			polinomio_dtor(pol);
		}

	}

}

//
// visualizza i polinomi inseriti
//
void visualizzapolinomi() {

	printf("\n");
	printf("Elenco polinomi inseriti:\n");
	printf("-------------------------\n");

	t_polinomio *pol;
	int i = 0;

	while ((pol = polinomiolist_getnext(polinomilist)) != NULL) {
		printf("%i) %s\n", ++i, polinomio_tostring(pol));
	}

}

//
// svuota lista dei polinomi
//
void svuotalistapolinomi(void) {

	if (domanda("Eliminare tutti i polinomi inseriti?") == 1)
	{
		polinomiolist_dtor(polinomilist);
		polinomilist = polinomiolist_ctor();
	}
}

//
// valuta i polinomi inseriti
//
void valutapolinomi(void) {
	printf("\n");
	printf("Valuta polinomi:\n");
	printf("----------------------\n");

	if (polinomilist == NULL || polinomilist->item == NULL)
	{
		printf("\n");
		printf("Nessun Polinomio inserito.\n");

		pausa();
		return;
	}


	printf("\n");
	printf("Inserisci il punto in cui valutare i polinomi: ");

	char s[16];
	fgets(s, 16, stdin);

	double d = atof(s);

	t_polinomio *pol;
	int i = 0;

	printf("\n");

	while ((pol = polinomiolist_getnext(polinomilist)) != NULL) {
		printf("%i) %s = %f\n", ++i, polinomio_tostring(pol), polinomio_valuta(pol, d));
	}

	pausa();
}

//
// operazioni sui polinomi
// 
void operazioni(void) {

	printf("\n");
	printf("Operazioni sui polinomi polinomi:\n");
	printf("---------------------------------\n");

	if (polinomilist == NULL || polinomilist->item == NULL)
	{
		printf("\n");
		printf("Nessun Polinomio inserito.\n");

		pausa();
		return;
	}

	
	char s[16];						// stringa di input	
	char *op;						// simbolo operazione inserita
	int m = 0;						// primo termine
	int n = 0;						// secondo termine
	t_polinomiolist *res = NULL;	// risultati delle operazioni

	// loop infinito
	for (;;)
	{
		// visualizza i polinomi inseriti
		visualizzapolinomi();

		// itera fino a quando non vengono inseriti valori corretti
		for (;;)
		{
			// chiede di inserire una operazione
			printf("\n");
			printf("Inserisci l'operazione oppure [INVIO] per terminare (Es. 1+3 somma il polinomio 1) con il polinomio 3): ");						
			fgets(s, 16, stdin);

			// esce se � stato premuto [INVIO]
			if (s[0] == '\n')
				return;

			// determina il tipo di operazione
			if ((op = strchr(s, '+')) != NULL || (op = strchr(s, '-')) != NULL || (op = strchr(s, '*')) != NULL || (op = strchr(s, '/')) != NULL)
			{

				// recupera il primo termine
				int i = op - s;
				char s2[16];
				strncpy(s2, s, i);
				s2[i] = '\0';
				m = atoi(s2);

				// recupera il secondo termine
				strcpy(s2, op + 1);
				n = atoi(s2);

				// verifica se i termini sono esatti
				if (m < 1 || n < 1 || m > (int)polinomiolist_getsize(polinomilist) || n > (int)polinomiolist_getsize(polinomilist))
				{
					printf("\n");
					printf("Operazione non valida!!!\n");
				}
				else
				{
					// operazione inserita ok. Esce dal ciclo
					break;
				}
			}
			else
			{
				printf("\n");
				printf("Operazione non valida!!!\n");
			}

		}

		// azzera la lista dei risultati
		if (res != NULL)
			polinomiolist_dtor(res);

		// istanzia la lista dei risultati
		res = polinomiolist_ctor();

		// recupera i polinomi selezionati
		t_polinomio *pm = polinomiolist_getelementat(polinomilist, m - 1);
		t_polinomio *pn = polinomiolist_getelementat(polinomilist, n - 1);

		printf("\n");
		printf("(%s) %c (%s) = ", polinomio_tostring(pm), *op, polinomio_tostring(pn));

		switch (*op)
		{
		case '+':
			polinomiolist_add(res, polinomio_somma(pm, pn));
			printf("%s\n", polinomio_tostring(res->item->polinomio));
			break;

		case '-':
			polinomiolist_add(res, polinomio_sottrai(pm, pn));
			printf("%s\n", polinomio_tostring(res->item->polinomio));
			break;

		case '/':
			res = polinomio_dividi(pm, pn);
			printf("\n");
			printf("Quoziente: %s ", polinomio_tostring(res->item->polinomio));
			printf("Resto: %s\n", polinomio_tostring(res->item->next->polinomio));
			break;

		case '*':
			polinomiolist_add(res, polinomio_moltiplica(pm, pn));
			printf("%s\n", polinomio_tostring(res->item->polinomio));
			break;

		default:
			break;
		}

		// chiede se salvare
		if (domanda("Vuoi salvare il risultato?") == 1)
		{
			// salva i polinomi
			t_polinomio *pol;
			while ((pol = polinomiolist_getnext(res)) != NULL) {
				if (pol->list->item->monomio->coefficiente != 0)
					polinomiolist_add(polinomilist, pol);
			}
		}
	}


}

//
// inserisce e valuta un trinomio di secondo grado
// 
void instrinomio(void) {

	printf("\n");
	printf("Inserisci e valuta un trinomio di secondo grado (ax^2 + bx + c):\n");
	printf("----------------------------------------------------------------\n");

	// coefficienti
	double a = 0;
	double b = 0;
	double c = 0;

	char s[16];

	printf("Inserisci il coefficiente a: ");
	fgets(s, 16, stdin);
	a = atof(s);

	printf("Inserisci il coefficiente b: ");
	fgets(s, 16, stdin);
	b = atof(s);

	printf("Inserisci il coefficiente c: ");
	fgets(s, 16, stdin);
	c = atof(s);

	// trinomio
	t_polinomio *trinomio = polinomio_creatrinomio(a, b, c);

	printf("\n");
	printf("Trinomio inserito: %s\n", polinomio_tostring(trinomio));

	// calcola le radici
	double radici[2];
	int flgx1 = 0;
	int flgx2 = 0;
	polinomio_radicitrinomio(a, b, c, radici, &flgx1, &flgx2);

	printf("\n");

	if (flgx1 == 0 && flgx2 == 0)
		printf("Non ci sono soluzioni reali per il trinomio inserito\n");
	else
	{
		printf("x1 = %f\n", radici[0]);
		if (flgx2 == 1) printf("x2 = %f\n", radici[1]);

	}

	if (domanda("Salvare il trinomio inserito?") == 1)
	{
		polinomiolist_add(polinomilist, polinomio_normalizza(trinomio));
	}


}

//
// fa una domanda all'utente alla quale si deve rispondere S/N
//
int domanda(char *testo)
{
	char s[16];

	do {
		printf("\n");
		printf("%s (S/N): ", testo);
		fgets(s, 16, stdin);
	} while (strcmp(s, "S\n") != 0 && strcmp(s, "s\n") != 0 && strcmp(s, "N\n") != 0 && strcmp(s, "n\n") != 0);

	// salva i polinomi
	if (strcmp(s, "S\n") == 0 || strcmp(s, "s\n") == 0)
		return 1;
	else
		return 0;

}

//
// pausa
//
void pausa(void) {
	printf("\n");
	printf("Premi [INVIO] per proseguire\n");
	getchar();
}

void test(void) {
	t_monomio *mon = monomio_parse("x^3");
	t_monomio *mon2 = monomio_parse("x^2");

	char *s = monomio_tostring(monomio_dividi(mon, mon2));

	printf("x -> %s\n", monomio_tostring(monomio_parse("x")));
	printf("-x -> %s\n", monomio_tostring(monomio_parse("-x")));
	printf("-x^2 -> %s\n", monomio_tostring(monomio_parse("-x^2")));
	printf("1.333333x^-2 -> %s\n", monomio_tostring(monomio_parse("1.333333x^-2")));
	printf("x^0 -> %s\n", monomio_tostring(monomio_parse("x^0")));
	printf("2x^0 -> %s\n", monomio_tostring(monomio_parse("2x^0")));
	printf("2x^2 -> %s\n", monomio_tostring(monomio_parse("2x^2")));
	printf("0x^0 -> %s\n", monomio_tostring(monomio_parse("0x^0")));
	printf("3x^0 -> %s\n", monomio_tostring(monomio_parse("3x^0")));

}
