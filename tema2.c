/* CAUIA Alexandru - 314CB */
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include "coada.h"
#include "lista.h"

int cmp(void *e1, void *e2)
{
    Tserial *serial1 = (Tserial *)e1;
    Tserial *serial2 = (Tserial *)e2;

    float rating1 = serial1->rating; //accesez rating-urile serialelor din structura
    float rating2 = serial2->rating;

    if (rating1 < rating2)
        return 1;
    else if (rating1 > rating2) //compar rating
        return -1;
    else
    {
        if (strcmp(serial1->nume, serial2->nume) > 0) //compar numele
            return 1;
        else
            return -1;
    }
}

void printSerial(void *e, FILE *out)
{
    Tserial *el = (Tserial *)e;
    fprintf(out, "(%s, %.1f)", el->nume, el->rating);
}

void printSerials(void *e, char *category, FILE *out)
{
    ACel p, el = (ACel)e;
    fprintf(out, "Categoria %s: [", category);
    for (p = el; p != NULL; p = p->urm)
    {
        if (p->urm == NULL)
        {
            printSerial(p->info, out);
        }
        else
        {
            printSerial(p->info, out);
            fprintf(out, ", ");
        }
    }
    fprintf(out, "].\n");
}

void read_function(char *numeFisier, FILE *fwrite, ACel Tendinte, ACel Documentare, ACel Tutoriale, ACel top10, AQ watch_later)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;

    f = fopen(numeFisier, "rt");
    if (f == NULL)
        return;

    while (getline(&line, &len, f) != -1)
    {
        char *functie = strtok(line, " "); // stochez primul cuvant in variabila functie
        if (functie[strlen(functie) - 1] == '\n') 
            functie[strlen(functie) - 1] = '\0'; //elimin \n
        if (functie[strlen(functie) - 1] == '\r')
            functie[strlen(functie) - 1] = '\0';
        if (strcmp(functie, "add") == 0) //compar cu add
        {
            char *ID_char = strtok(NULL, " "); //il citesc pe ID
            int ID = atoi(ID_char); // il convertesc la int si il stochez intr-o variabila
            char *nume_char = strtok(NULL, " ");
            char *rating_char = strtok(NULL, " ");
            float rating = atof(rating_char);
            char *numar_sezoane = strtok(NULL, " ");
            int nr_sezoane = atoi(numar_sezoane);

            Tserial *serial = malloc(sizeof(Tserial)); //aloc memorie pentru structura
            if (serial == NULL)
                return;
            serial->nume = (char *)malloc((strlen(nume_char) + 1) * sizeof(char)); 
            strcpy(serial->nume, nume_char);
            serial->ID = ID;
            serial->rating = rating;             
            serial->nr_sezoane = nr_sezoane;
            //am format serialul

            int max_sezoane[10];
            int max_episoade[20];
            int i = 0, j = 0;

            while (i < nr_sezoane) //pana cand i e diferit de nr de sezoane
            {
                j = 0;
                AQ sezon = malloc(sizeof(TCoada)); //aloc coada sezon
                IC(sezon) = NULL;
                SC(sezon) = NULL;
                char *episoade = strtok(NULL, " "); //citesc nr de episoade
                max_sezoane[i] = atoi(episoade);    //il pun intr-un array
                sezon->info = &max_sezoane[i];      //apoi in campul de info al cozii
                while (j < max_sezoane[i])         //pana cand j ajunge la nr de episoade
                {
                    char *timpul_episod = strtok(NULL, " "); //citesc durata episodului
                    max_episoade[j] = atoi(timpul_episod);   //pun in array durata
                    ACel episod = malloc(sizeof(Tcel));      //aloc o celula generica
                    episod->info = &max_episoade[j];         //in informatie pun durata episodului
                    episod->urm = NULL;
                    if (VIDA(sezon))
                    {
                        IC(sezon) = episod; //cand e singur pointeaza inceputul si sfarsitul la episod
                        SC(sezon) = episod;
                    }
                    else
                    {
                        SC(sezon)->urm = episod; //leg prima de urmatoarea
                        SC(sezon) = episod;      //sfarsitul cozii pointeza la ultimul
                    }
                    j++;
                }

                i++;
            }

            if (ID == 1)
            {
                InsLGOrd(&Tendinte, serial, cmp, fwrite);
            }
            else if (ID == 2)
            {
                InsLGOrd(&Documentare, serial, cmp, fwrite);  // in dependenta de ID inserez in lista
            }
            else if (ID == 3)
            {
                InsLGOrd(&Tutoriale, serial, cmp, fwrite);
            }
            else if (ID == 4)
            {
                InsLGOrd(&top10, serial, cmp, fwrite);
            }
        }
        else if (strcmp(functie, "show") == 0) //daca cuvantul stocat e show
        {
            char *categorie = strtok(NULL, " ");
            if (categorie[strlen(categorie) - 1] == '\n')
                categorie[strlen(categorie) - 1] = '\0';
            if (categorie[strlen(categorie) - 1] == '\r')
                categorie[strlen(categorie) - 1] = '\0';
            if(strcmp(categorie, "later") == 0)
            {
                print_coada(watch_later, fwrite, printSerials); //printez coada
            }
            else if (strcmp(categorie, "top10") == 0) //daca dupa show urmeaza top10
            {
                printSerials(top10, "top10", fwrite); //printez serialele din top10
            }
            else
            {
                int Category_int = atoi(categorie);
                if (Category_int == 1)
                    printSerials(Tendinte, "1", fwrite);

                else if (Category_int == 2)
                    printSerials(Documentare, "2", fwrite);

                else if (Category_int == 3)
                    printSerials(Tutoriale, "3", fwrite);
            }

        }
        else if(strcmp(functie, "add_top") == 0)
        {
            char *pozitie_char = strtok(NULL, " ");
            int pozitie = atoi(pozitie_char);
            char *nume_char = strtok(NULL, " ");
            char *rating_char = strtok(NULL, " ");
            float rating = atof(rating_char);
            char *numar_sezoane = strtok(NULL, " ");
            int nr_sezoane = atoi(numar_sezoane);

            Tserial *serial = malloc(sizeof(Tserial));
            if (serial == NULL)
                return;
            serial->nume = (char *)malloc((strlen(nume_char) + 1) * sizeof(char));
            strcpy(serial->nume, nume_char);
            serial->ID = pozitie;
            serial->rating = rating;
            serial->nr_sezoane = nr_sezoane;


            int max_sezoane[10];
            int max_episoade[20];
            int i = 0, j = 0;

            while (i != serial->nr_sezoane) //pana cand i e diferit de nr de sezoane
            {
                j = 0;
                AQ sezon = malloc(sizeof(TCoada)); //aloc coada sezon
                IC(sezon) = NULL;
                SC(sezon) = NULL;
                char *episoade = strtok(NULL, " "); //citesc nr de episoade
                max_sezoane[i] = atoi(episoade);    //il pun intr-un array
                sezon->info = &max_sezoane[i];      //apoi in campul de info al cozii
                while (j != atoi(episoade))         //pana cand j ajunge la nr de episoade
                {
                    char *timpul_episod = strtok(NULL, " "); //citesc durata episodului
                    max_episoade[j] = atoi(timpul_episod);   //pun in array durata
                    ACel episod = malloc(sizeof(Tcel));      //aloc o celula generica
                    episod->info = &max_episoade[j];         //in informatie pun durata episodului
                    episod->urm = NULL;
                    if (VIDA(sezon))
                    {
                        IC(sezon) = episod; //cand e singur pointeaza inceputul si sfarsitul la episod
                        SC(sezon) = episod;
                    }
                    else
                    {
                        SC(sezon)->urm = episod; //leg prima de urmatoarea
                        SC(sezon) = episod;      //sfarsitul cozii pointeza la ultimul
                    }
                    j++;
                }

                i++;
            }
            Inserare_top_zece(&top10, serial, pozitie, fwrite);
            printSerials(top10, "top10", fwrite);
        }
        else if(strcmp(functie, "later") == 0)
        {
            char* serial_asteptare = strtok(NULL, " ");
            if (serial_asteptare[strlen(serial_asteptare) - 1] == '\n')
                serial_asteptare[strlen(serial_asteptare) - 1] = '\0';
            if (serial_asteptare[strlen(serial_asteptare) - 1] == '\r')
                serial_asteptare[strlen(serial_asteptare) - 1] = '\0';
            ACel serial_extras = gaseste_serial(&Tendinte, &Documentare, &Tutoriale, &top10, serial_asteptare);
            introdu_serial(watch_later, serial_extras, fwrite); //introduc serial in coada watch_later
        }

    }
}


int main(int argc, char *argv[])
{
    ACel head_ctg_1 = NULL;
    ACel head_ctg_2 = NULL;
    ACel head_ctg_3 = NULL;
    ACel head_ctg_4 = NULL;
    FILE *fwrite;
    fwrite = fopen(argv[2], "wt");
    AQ watch_later = malloc(sizeof(TCoada));
    watch_later->ic = NULL;
    watch_later->sc = NULL;
    read_function(argv[1], fwrite, head_ctg_1, head_ctg_2, head_ctg_3, head_ctg_4, watch_later);
    fclose(fwrite);
    return 0;
}
