/* RUSU HORIA - 311 CD */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functii.h"
#define MAX_LIMIT 101

int main () {
    FILE *input = fopen("tema1.in", "r");
    FILE *output = fopen("tema1.out", "w");
    int numar_comenzi;
    char comanda[MAX_LIMIT];
    fscanf (input, "%d", &numar_comenzi);
    Coada *coada = initializare_Coada(output);
    Tren *tren = initializare_Tren(output);
    for (int i = 0; i < numar_comenzi; i++) {
        fscanf (input, "%s", comanda);
        if (strcmp(comanda, "SEARCH_LEFT") == 0 || strcmp(comanda, "SEARCH_RIGHT") == 0 || 
            strcmp(comanda, "WRITE") == 0 || strcmp(comanda, "INSERT_RIGHT") == 0 || 
            strcmp(comanda, "INSERT_LEFT") == 0 || strcmp(comanda, "SEARCH") == 0) {
                char sir[MAX_LIMIT];
                fscanf(input, "%s", sir);
                strcat(comanda, " ");
                strcat(comanda, sir);
                adaugare_in_coada(output, coada, comanda);
        } else if (strcmp(comanda, "EXECUTE") == 0) {
            EXECUTE(output, coada, tren);
        } else if (strcmp(comanda, "SHOW_CURRENT") == 0) {
            SHOW_CURRENT(output, tren);
        } else if (strcmp(comanda, "SHOW") == 0) {
            SHOW(output, tren);
        } else if (strcmp(comanda, "SWITCH") == 0) {
            SWITCH(output, coada);
        } else {
            adaugare_in_coada(output, coada, comanda);
        }
    }
    elibereaza_Coada(coada);
    elibereaza_Tren(tren);
    fclose(input);
    fclose(output);
    return 0;
}




