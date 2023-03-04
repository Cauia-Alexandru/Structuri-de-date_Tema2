/* CAUIA Alexandru - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "coada.h"

int InsLGOrd(ACel *aL, void *ae, TFCmp f, FILE *fwrite)
{ 
    ACel current = malloc(sizeof(Tcel)); //aloc celula care trebuie s-o inserez
    if (!current)
        return 0;

    current->info = ae;  // ae va fi informatia celulei 
    current->urm = NULL;
    ACel aux = *aL, ant = NULL; //aux - capul listei
    char *name = ((Tserial *)(current->info))->nume; //accesez numele din informatia celulei

    if (*aL == NULL)
    {
        *aL = current; // daca lista e goala, current devine capul listei
        fprintf(fwrite, "Serialul %s a fost adaugat la pozitia 1.\n", name);
    }
    else
    {
        int pozitie = 1;
        while (aux != NULL) //parcurg lista
        {
            if (f(aux->info, ae) >= 0) //daca functia de comparatie returneaza >= 0
                break; //ies din while si inserez in fata

            ant = aux;
            aux = aux->urm;  //daca nu, parcurg mai departe
            pozitie++; //incrementez pozitia
        }

        if (ant == NULL)
        {
            current->urm = *aL; //daca ant e null, current devine capul listei
            *aL = current;
            fprintf(fwrite, "Serialul %s a fost adaugat la pozitia 1.\n", name);
        }
        else
        {
            current->urm = aux; //inserez in lista in fata lui aux
            ant->urm = current;
            fprintf(fwrite, "Serialul %s a fost adaugat la pozitia %d.\n", name, pozitie);
        }
    }
    return 1;
}

int Inserare_top_zece(ACel *aL, void* ae, int k, FILE *fwrite)
{
    ACel current = malloc(sizeof(Tcel));
    if (!current)
        return 0;
    current->info = ae;
    current->urm = NULL;
    ACel aux = *aL, ant = NULL;
    int i;
    if (k == 1) // daca trebuie sa inserez top1
    {
        current->urm = *aL;
        *aL = current; //current devine capul listei

    }
    else
    {

        for (i = 1; i < k; i++)
        {
            ant = aux;
            aux = aux->urm; //parcurg lista pana la k
            if(aux == NULL) //daca ajung la capat
                break;

        }

        current->urm = aux; //inserez inainte
        ant->urm = current;

    }
    ant = NULL; //resetez pozitiile
    aux = *aL;
    int counter = 0;
    for (; aux->urm != NULL; counter++)
    {
        ant = aux;
        aux = aux->urm; //parcurg lista
    }

    if (counter == 10) //daca sunt mai multe celule decat 10
    {
        ant->urm = NULL; //rup legatura
    }
    return 1;
}
