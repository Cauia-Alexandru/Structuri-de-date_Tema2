/* CAUIA Alexandru - 314CB */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "coada.h"


void introdu_serial(AQ later, ACel serial, FILE *fwrite)
{

    if (VIDA(later))
    {
        IC(later) = serial;
        SC(later) = serial; //daca coada e vida inceputul si sfarsitul cozii pointeza la celula
        
    }
    else
    {
        SC(later)->urm = serial; 
        SC(later) = serial;  //mut sfarsitul cozii la celula introdusa
    }
    ACel aux = IC(later);
    int count = 1;
    for (; aux->urm != NULL; aux = aux->urm)
    {
        count++; //aflu pozitia serialului in coada
    }
    fprintf(fwrite, "Serialul %s se afla in coada de asteptare pe pozitia %d.\n", ((Ser_info)(serial->info))->nume, count);
}

ACel gaseste_serial(ACel *lista_unu, ACel *lista_doi, ACel *lista_trei, ACel *lista_patru, char *nume)
{
    ACel aux = *lista_unu, ant = NULL; //aux e capul primei liste

    for (; aux != NULL; ant = aux, aux = aux->urm) //parcurg lista 
    {
        char *nume_gasit = ((Tserial *)(aux->info))->nume; 
        if (strcmp(nume, nume_gasit) == 0) //compar numele din celula cu cel dat ca parametru
        {
            if (ant == NULL)
            {
                *lista_unu = aux->urm; //elimin capul listei
            }
            else
            {
                ant->urm = aux->urm; //sar peste celula care contine numele identic cu cel cautat
            }
            aux->urm = NULL;
            return aux; //returnez celula gasita
        }
    }

    aux = *lista_doi;
    ant = NULL;
    for (; aux != NULL; ant = aux, aux = aux->urm)
    {
        char *nume_gasit = ((Tserial *)(aux->info))->nume;
        if (strcmp(nume, nume_gasit) == 0)
        {
            if (ant == NULL)
            {
                *lista_doi = aux->urm;
            }
            else
            {
                ant->urm = aux->urm;
            }
            aux->urm = NULL;
            return aux;
        }
    }
    aux = *lista_trei;
    ant = NULL;
    for (; aux != NULL; ant = aux, aux = aux->urm)
    {
        char *nume_gasit = ((Tserial *)(aux->info))->nume;
        if (strcmp(nume, nume_gasit) == 0)
        {
            if (ant == NULL)
            {
                *lista_trei = aux->urm;
            }
            else
            {
                ant->urm = aux->urm;
            }
            aux->urm = NULL;
            return aux;
        }
        //printf("%d\n", strcmp(nume, nume_gasit));
    }
    aux = *lista_patru;
    ant = NULL;
    for (; aux != NULL; ant = aux, aux = aux->urm)
    {
        char *nume_gasit = ((Tserial *)(aux->info))->nume;
        if (strcmp(nume, nume_gasit) == 0)
        {
            if (ant == NULL)
            {
                *lista_patru = aux->urm;
            }
            else
            {
                ant->urm = aux->urm;
            }
            aux->urm = NULL;
            return aux;
        }
    }
    return NULL;
}

void print_coada(void* later, FILE* fwrite, void (*printS)(void*, char*, FILE*))
{
    AQ coada = (AQ)later;
    ACel head = IC(coada);
    printS(head, "later", fwrite);
}