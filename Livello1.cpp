#include <stdio.h>

#define DIMENSIONE 45

void printTable(int Livello1[DIMENSIONE][DIMENSIONE]) {
    for (int i = 0; i < DIMENSIONE; i++) {
        printf("\t\t\t\t\t\t");
        for (int j = 0; j < DIMENSIONE; j++) {
            printf("%d ", Livello1[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int Livello1[DIMENSIONE][DIMENSIONE];

    // Popolamento della matrice con 0
    for (int i = 0; i < DIMENSIONE; i++) {
        for (int j = 0; j < DIMENSIONE; j++) {
            // Imposta 1 sui bordi, sulle righe e sulle colonne 2, 4, 6 e 8
            if (i == 0 || i == DIMENSIONE - 1 || j == 0 || j == DIMENSIONE - 1 || i % 2 != 1 || j % 2 != 1) {
                Livello1[i][j] = 1;
            }
            else {
                Livello1[i][j] = 0;
            }
        }
    }

    // Stampa della tabella
    printTable(Livello1);

    return 0;
}
