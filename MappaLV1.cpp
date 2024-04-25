#include <stdio.h>

#define ROWS 5
#define COLS 5

int main() {
    // Definizione della matrice per la tabella
    char table[ROWS][COLS] = {
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '}
    };

    // Stampa della tabella
    printf("\t\t\t\t\tI-----+-----+-----+-----+-----I\n");
    for (int i = 0; i < ROWS; i++) {
        printf("\t\t\t\t\t|  %c  |  %c  |  %c  |  %c  |  %c  |\n", table[i][0], table[i][1], table[i][2], table[i][3], table[i][4]);
        if (i == 4) {
            printf("\t\t\t\t\t!-----+-----+-----+-----+-----!\n");
        }
        else {
            printf("\t\t\t\t\t|-----+-----+-----+-----+-----|\n");
        }
    }
}