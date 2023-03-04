functii_coada.c----------------------------------------------------------------------------
introdu serial--->
Primeste ca parametri coada in care inserez, celula, file. Daca coada e vida IC si SC pointeaza
la celula inserata, altfel utima celula va pointa catre celula introdusa si SC se muta la ea.


gaseste serial---->
Dau ca parametru toate 4 liste in care voi cauta numele primit.Parcurg lista cu aux care e 
capul listei si cu ant. Cu strcmp compar numele si daca il gasesc sar peste el. Daca e cap de
lista, mut capul, daca nu, sar peste celula

functii_liste.c-----------------------------------------------------------------------------

InsLGOrd----->
Primesc ca parametri celula care trebuie so inserez, un void*, functia de comparare, si file.
Daca lista e goala, celula care trebuie s-o inserez devine capul listei, altfel cu un while 
parcurg lista si cu ajutorul functiei de comparare. Daca trebuie sa inserez inainte cu un break ies din 
while si restabilesc legaturile in functir=e de 2 cazuri. Daca trebuie sa fie cap de lista si daca nu.

Insrare_top_zece----->
Daca numarul dat ca parametru din in_file e 1, trebuie sa inserez la inceput, deci va fi capul listei.
Daca nu parcurg lista pana la k si inserez. Apoi cu ajutorul unui for aflu pozitia unde a fost inserat.




