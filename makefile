build:
	gcc -g -o tema2 -Wall -std=c11 functii_coada.c functii_liste.c tema2.c 

.PHONY: clean
clean:
	rm tema2