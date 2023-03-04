/* CAUIA Alexandru - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "lista.h"

#ifndef _coada_
#define _coada_

typedef struct coada
{
    void* info;
    ACel ic, sc;
}TCoada, *AQ;

typedef struct 
{
    int ID;
    char* nume;
    float rating;
    int nr_sezoane;
}Tserial, *Ser_info;


#define IC(a) 	(((AQ)(a))->ic)
#define SC(a) 	(((AQ)(a))->sc)
#define VIDA(a) 		((IC(a) == SC(a)) && IC(a) == NULL)

ACel gaseste_serial(ACel *lista_unu, ACel *lista_doi, ACel *lista_trei, ACel *lista_patru, char *nume);
void introdu_serial(AQ later, ACel serial, FILE* fwrite);
void print_coada(void* later, FILE* fwrite, void (*printS)(void*, char*, FILE*));













#endif