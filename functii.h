/* RUSU HORIA - 311 CD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LIMIT 101

typedef struct tren {
    struct vagon *sentinela;
    struct vagon *mecanic;
} Tren;

typedef struct vagon {
    char caracter;
    struct vagon *next;
    struct vagon *prev;
} Vagon;


Tren* initializare_Tren(FILE *output) {
    Tren* tren = (Tren*) malloc(sizeof(struct tren));
        if (tren == NULL) {
            fprintf(output, "Eroare la alocarea memoriei pentru tren\n");
            exit(1);
        }
    tren->sentinela = (Vagon*) malloc(sizeof (struct vagon));
    tren->mecanic = (Vagon *) malloc(sizeof(struct vagon));
    tren->mecanic->caracter = '#';
    tren->sentinela->next = tren->mecanic;
    tren->sentinela->prev = tren->mecanic;
    tren->mecanic->next = tren->sentinela;
    tren->mecanic->prev = tren->sentinela;
    return tren;
}

typedef struct coada {
    struct comanda *front;
    struct comanda *rear;
    int size;
} Coada;

typedef struct comanda {
    struct comanda *prev;
    struct comanda *next;
    char command[MAX_LIMIT];
} Comanda;

Coada* initializare_Coada(FILE *output) {
    Coada* coada = (Coada*) malloc(sizeof(struct coada));
    if (coada == NULL) {
        fprintf(output, "Eroare la alocarea memoriei pentru coada\n");
        exit(1);
    }
    coada->size = 0;
    coada->front = NULL;
    coada->rear = NULL;
    return coada;
}

void adaugare_in_coada(FILE *output, Coada *coada, char *comanda) {
    Comanda *newCommand = (Comanda*) malloc(sizeof(struct comanda));
    strcpy(newCommand->command, comanda);
    if (coada->size == 0) {
        coada->front = newCommand;
        coada->rear = newCommand;
        coada->rear->next = NULL;
        coada->front->prev = NULL;
    } else {
        newCommand->prev = coada->rear;
        coada->rear->next = newCommand;
        coada->rear = newCommand;
        newCommand->next = NULL;
        coada->rear->next = NULL;
    }
    coada->size ++;
}

void MOVE_RIGHT(Tren *tren) {
    if (tren->mecanic->next == tren->sentinela) {
        Vagon* newVagon = (Vagon*) malloc(sizeof(struct vagon));
        newVagon->caracter = '#';
        newVagon->prev = tren->mecanic;
        newVagon->next = tren->sentinela;
        tren->mecanic->next = newVagon;
        tren->sentinela->prev = newVagon;
        tren->mecanic = newVagon;
    } else {
        tren->mecanic = tren->mecanic->next;
    }
}

void MOVE_LEFT(Tren *tren) {
    if (tren->mecanic->prev == tren->sentinela) {
        tren->mecanic = tren->sentinela->prev;
    } else {
        tren->mecanic = tren->mecanic->prev;
    }
}

void WRITE(Tren *tren, char newCaracter) {
    tren->mecanic->caracter = newCaracter;
}

void CLEAR_CELL(Tren *tren) {
    if (tren->mecanic->prev == tren->sentinela && tren->mecanic->next == tren->sentinela) {
        Vagon *temporar = tren->mecanic;
        free(temporar);
        Vagon *nou = (Vagon*) malloc(sizeof(struct vagon));
        nou->next = tren->sentinela;
        nou->prev = tren->sentinela;
        tren->sentinela->next = nou;
        tren->sentinela->prev = nou;
        nou->caracter = '#';
        tren->mecanic = nou;
    } else if (tren->mecanic->prev == tren->sentinela && tren->mecanic->next != tren->sentinela) {
        Vagon *temporar = tren->mecanic;
        tren->sentinela->next = tren->mecanic->next;
        tren->mecanic->next->prev = tren->sentinela;
        tren->mecanic = tren->sentinela->prev;
        tren->mecanic->next = tren->sentinela;
        free(temporar);
    } else if (tren->mecanic->prev != tren->sentinela && tren->mecanic->next == tren->sentinela) {
        Vagon *temporar = tren->mecanic;
        tren->mecanic = tren->mecanic->prev;
        tren->mecanic->next = tren->sentinela;
        tren->sentinela->prev = temporar->prev;
        free(temporar);
    } else {
        Vagon *temporar = tren->mecanic;
        tren->mecanic = tren->mecanic->prev;
        tren->mecanic->next = temporar->next;
        tren->mecanic->next->prev = temporar->prev;
        free(temporar);
    }
}

void CLEAR_ALL(Tren *tren) {
    Vagon *curent = tren->sentinela->next;
    while (curent->next != tren->sentinela) {
        Vagon *temporar = curent;
        curent = curent->next;
        free(temporar);
    }
    tren->sentinela->next = curent;
    curent->prev = tren->sentinela;
    tren->mecanic = curent;
    tren->mecanic->caracter = '#';
}

void INSERT_RIGHT(Tren *tren, char caracter) {
    Vagon* newVagon = (Vagon*) malloc(sizeof(struct vagon));
    if (tren->mecanic->next == tren->sentinela) {
        tren->mecanic->next = newVagon;
        newVagon->prev = tren->mecanic;
        newVagon->next = tren->sentinela;
        tren->sentinela->prev = newVagon;
        tren->mecanic = newVagon;
        newVagon->caracter = caracter;
    } else {
        newVagon->next = tren->mecanic->next;
        newVagon->prev = tren->mecanic;
        tren->mecanic->next->prev = newVagon;
        tren->mecanic->next = newVagon;
        tren->mecanic = newVagon;
        newVagon->caracter = caracter;
    }
}

void INSERT_LEFT(FILE *output, Tren *tren, char caracter) {
    if (tren->mecanic->prev == tren->sentinela) {
        fprintf(output, "ERROR\n");
    } else {
        Vagon* newVagon = (Vagon*) malloc(sizeof(struct vagon));
        newVagon->prev = tren->mecanic->prev;
        newVagon->next = tren->mecanic;
        tren->mecanic->prev->next = newVagon;
        tren->mecanic->prev = newVagon;
        tren->mecanic = newVagon;
        newVagon->caracter = caracter;
    }
}

void SEARCH(FILE *output, Tren *tren, char *sir) {
    Vagon *curent = tren->mecanic;
    Vagon *temporar = curent;
    int gasit = 0;
    int trecut = 0;
    char copie_sir[MAX_LIMIT];
    strcpy(copie_sir, sir);
    int i = 0;
    while (copie_sir[i] != '\0' && temporar->caracter == copie_sir[i] && (temporar != tren->mecanic || trecut != 1)) {
        i++;
        if (temporar->next == tren->sentinela) {
            temporar = tren->sentinela->next;
            trecut = 1;
        } else {
            temporar = temporar->next;
        }
    }
    if (copie_sir[i] == '\0') {
        gasit = 1;
    }
    if (gasit == 0) {
        curent = curent->next;
        while (curent != tren->mecanic) {
            strcpy(copie_sir, sir);
            int i = 0;
            temporar = curent;
            while (copie_sir[i] != '\0' && temporar->caracter == copie_sir[i] && temporar != tren->mecanic) {
                i++;
                if (temporar->next == tren->sentinela) {
                    temporar = tren->sentinela->next;
                } else {
                    temporar = temporar->next;
                }
            }
            if (copie_sir[i] == '\0') {
                gasit = 1;
                tren->mecanic = curent;
                break;
            }
            if (curent->next == tren->sentinela) {
                curent = tren->sentinela->next;
            } else {
                curent = curent->next;
            }
        }
    }
    if (gasit == 0) {
        fprintf(output, "ERROR\n");
    }
}

void SEARCH_LEFT(FILE *output, Tren *tren, char *sir) {
    Vagon *curent = tren->mecanic;
    int gasit = 0;
    while (curent != tren->sentinela) {
        char copie_sir[MAX_LIMIT];
        strcpy(copie_sir, sir);
        int i = 0;
        Vagon *temporar = curent;
        while (copie_sir[i] != '\0' && temporar != tren->sentinela && temporar->caracter == copie_sir[i]) {
            i++;
            temporar = temporar->prev;
        }
        if (copie_sir[i] == '\0') {
            gasit = 1;
            tren->mecanic = temporar->next;
            break;
        }
        curent = curent->prev;
    }
    if (gasit == 0) {
        fprintf(output, "ERROR\n");
    }
}

void SEARCH_RIGHT(FILE *output, Tren *tren, char *sir) {
    Vagon *curent = tren->mecanic;
    int gasit = 0;
    while (curent != tren->sentinela) {
        char copie_sir[MAX_LIMIT];
        strcpy(copie_sir, sir);
        int i = 0;
        Vagon *temporar = curent;
        while (copie_sir[i] != '\0' && temporar != tren->sentinela && temporar->caracter == copie_sir[i]) {
            i++;
            temporar = temporar->next;
        }
        if (copie_sir[i] == '\0') {
            gasit = 1;
            tren->mecanic = temporar->prev;
            break;
        }
        curent = curent->next;
    }
    if (gasit == 0) {
        fprintf(output, "ERROR\n");
    }
}

void SHOW_CURRENT(FILE *output, Tren *tren) {
    fprintf(output, "%c\n", tren->mecanic->caracter);
}

void SHOW(FILE *output, Tren *tren) {
    Vagon *curent = tren->sentinela->next;
    while (curent != tren->sentinela) {
        if (curent == tren->mecanic) {
            fprintf(output, "|");
            fprintf(output, "%c", tren->mecanic->caracter);
            fprintf(output, "|");
        } else {
            fprintf(output, "%c", curent->caracter);
        }
        curent = curent->next;
    }
    fprintf(output, "\n");
}

void SWITCH(FILE *output, Coada *coada) {
    if (coada == NULL || coada->front == NULL || coada->front == coada->rear) {
        return;
    }
    Comanda *current = coada->front;
    while (current != NULL) {
        Comanda *temporar = current->next;
        current->next = current->prev;
        current->prev = temporar;
        current = temporar;
    }
    Comanda *aux = coada->front;
    coada->front = coada->rear;
    coada->rear = aux;
    return;
}

void EXECUTE(FILE *output, Coada *coada, Tren *tren) {
    if (coada->size == 0) {
        return;
    }
    Comanda *comanda = coada->front;
    if (strncmp(comanda->command, "SEARCH_LEFT", 11) == 0) {
        char* sir = (char*) malloc(strlen(comanda->command + 12) + 1);
        strcpy(sir, comanda->command + 12);
        SEARCH_LEFT(output, tren, sir);
        free(sir);
    } else if (strncmp(comanda->command, "SEARCH_RIGHT", 12) == 0) {
        char* sir = (char*) malloc(strlen(comanda->command + 13) + 1);
        strcpy(sir, comanda->command + 13);
        SEARCH_RIGHT(output, tren, sir);
        free(sir);
    } else if (strcmp(comanda->command, "MOVE_RIGHT") == 0) {
        MOVE_RIGHT(tren);
    } else if (strcmp (comanda->command, "MOVE_LEFT") == 0) {
        MOVE_LEFT(tren);
    } else if (strncmp(comanda->command, "WRITE", 5) == 0) {
        char caracter = comanda->command[6];
        WRITE(tren, caracter);
    } else if (strcmp(comanda->command, "CLEAR_CELL") == 0) {
        CLEAR_CELL(tren);
    } else if (strcmp(comanda->command, "CLEAR_ALL") == 0) {
        CLEAR_ALL(tren);
    } else if (strncmp(comanda->command, "INSERT_LEFT", 11) == 0) {
        char caracter = comanda->command[12];
        INSERT_LEFT(output, tren, caracter);
    } else if (strncmp(comanda->command, "INSERT_RIGHT", 12) == 0) {
        char caracter = comanda->command[13];
        INSERT_RIGHT(tren, caracter);
    } else if (strncmp(comanda->command, "SEARCH", 6) == 0) {
        char* sir = (char*) malloc(strlen(comanda->command + 7) + 1);
        strcpy(sir, comanda->command + 7);
        SEARCH(output, tren, sir);
        free(sir);
    }
    coada->front = comanda->next;
    free(comanda);
    if (coada->front == NULL) {
        coada->rear = NULL;
    } else if (coada->front == coada->rear) {
        coada->front->prev = NULL;
        coada->front->next = NULL;
        coada->rear->prev = NULL;
        coada->rear->next = NULL;
    } else {
        coada->front->prev = NULL;
    }
    coada->size--;
}

void elibereaza_Coada(Coada *coada) {
    while (coada->front != NULL) {
        Comanda *temp = coada->front;
        coada->front = coada->front->next;
        free(temp);
    }
    coada->size = 0;
    free(coada);
}

void elibereaza_Tren(Tren *tren) {
    Vagon *curent = tren->sentinela->next;
    while (curent != tren->sentinela) {
        Vagon *temp = curent;
        curent = curent->next;
        free(temp);
    }
    free(tren->sentinela);
    free(tren);
}

