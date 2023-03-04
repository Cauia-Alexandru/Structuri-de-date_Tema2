/* CAUIA Alexandru - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#ifndef _lista_
#define _lista_

typedef struct cel
{
    struct cel * urm;
    void* info;

}Tcel, *ACel;


typedef int (*TFCmp)(void*, void*);
int InsLGOrd(ACel* aL, void* ae, TFCmp f, FILE *fwrite);
int Inserare_top_zece(ACel *aL, void* ae, int k, FILE *fwrite);


#endif