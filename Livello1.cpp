#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5

// Funzione per muovere i nemici in modo casuale o intelligente alternato
void moveEnemies(char table[ROWS][COLS], int playerRow, int playerCol) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (table[i][j] == 'N') {
                int moveRow = 0;
                int moveCol = 0;

                // Scegli casualmente se muoversi in modo casuale o intelligente
                int randomMove = rand() % 2; // Genera un numero casuale da 0 a 1
                if (randomMove == 0) {
                    // Muovi in modo casuale
                    int direction = rand() % 4; // Genera un numero casuale da 0 a 3 per rappresentare la direzione
                    switch (direction) {
                    case 0: // Su
                        if (i > 0 && table[i - 1][j] != 'P' && table[i - 1][j] != 'N' && table[i - 1][j] != 'C') {
                            moveRow = -1;
                        }
                        break;
                    case 1: // Giù
                        if (i < ROWS - 1 && table[i + 1][j] != 'P' && table[i + 1][j] != 'N' && table[i + 1][j] != 'C') {
                            moveRow = 1;
                        }
                        break;
                    case 2: // Sinistra
                        if (j > 0 && table[i][j - 1] != 'P' && table[i][j - 1] != 'N' && table[i][j - 1] != 'C') {
                            moveCol = -1;
                        }
                        break;
                    case 3: // Destra
                        if (j < COLS - 1 && table[i][j + 1] != 'P' && table[i][j + 1] != 'N' && table[i][j + 1] != 'C') {
                            moveCol = 1;
                        }
                        break;
                    }
                }
                else {
                    // Muovi in modo intelligente
                    int distRow = playerRow - i;
                    int distCol = playerCol - j;

                    if (abs(distRow) > abs(distCol)) {
                        if (distRow < 0 && table[i - 1][j] != 'P' && table[i - 1][j] != 'N' && table[i - 1][j] != 'C') {
                            moveRow = -1;
                        }
                        else if (distRow > 0 && table[i + 1][j] != 'P' && table[i + 1][j] != 'N' && table[i + 1][j] != 'C') {
                            moveRow = 1;
                        }
                        else {
                            if (distCol < 0 && table[i][j - 1] != 'P' && table[i][j - 1] != 'N' && table[i][j - 1] != 'C') {
                                moveCol = -1;
                            }
                            else if (distCol > 0 && table[i][j + 1] != 'P' && table[i][j + 1] != 'N' && table[i][j + 1] != 'C') {
                                moveCol = 1;
                            }
                        }
                    }
                    else {
                        if (distCol < 0 && table[i][j - 1] != 'P' && table[i][j - 1] != 'N' && table[i][j - 1] != 'C') {
                            moveCol = -1;
                        }
                        else if (distCol > 0 && table[i][j + 1] != 'P' && table[i][j + 1] != 'N' && table[i][j + 1] != 'C') {
                            moveCol = 1;
                        }
                        else {
                            if (distRow < 0 && table[i - 1][j] != 'P' && table[i - 1][j] != 'N' && table[i - 1][j] != 'C') {
                                moveRow = -1;
                            }
                            else if (distRow > 0 && table[i + 1][j] != 'P' && table[i + 1][j] != 'N' && table[i + 1][j] != 'C') {
                                moveRow = 1;
                            }
                        }
                    }
                }

                // Muovi il nemico in base alla direzione calcolata
                if (moveRow != 0 && table[i + moveRow][j] != 'P' && table[i + moveRow][j] != 'N' && table[i + moveRow][j] != 'C') {
                    table[i][j] = ' ';
                    table[i + moveRow][j] = 'N';
                }
                else if (moveCol != 0 && table[i][j + moveCol] != 'P' && table[i][j + moveCol] != 'N' && table[i][j + moveCol] != 'C') {
                    table[i][j] = ' ';
                    table[i][j + moveCol] = 'N';
                }
            }
        }
    }
}


// Funzione per generare i nemici in posizioni casuali
void generateEnemies(char table[ROWS][COLS]) {
    int count = 0;
    while (count < 2) {
        int row = rand() % 5;
        int col = rand() % 5;
        if (table[row][col] == ' ') {
            table[row][col] = 'N';
            count++;
        }
    }
}

int main() {
    // Inizializzazione del generatore di numeri casuali
    srand(time(NULL));

    // Definizione della matrice per la tabella
    char table[ROWS][COLS] = {
        {' ', ' ', ' ', ' ', ' '},
        {'C', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', 'P', ' '}
    };

    // Posizione iniziale del personaggio
    int playerRow = 4;
    int playerCol = 3;

    // Posizione della chiave
    int keyRow = 1;
    int keyCol = 0;

    generateEnemies(table);

    // Legenda del gioco
    printf("Personaggio(P)\n");
    printf("Nemico(N)\n");
    printf("Chiave(C)\n");

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

    char direction;

    while (1) {
        printf("In che direzione vuoi muoverti? (w/a/s/d): ");
        scanf(" %c", &direction); // %c per leggere un singolo carattere

        // Muovi il personaggio in base alla direzione
        switch (direction) {
        case 'w': // Su
            if (playerRow > 0) {
                if (table[playerRow - 1][playerCol] == 'N') {
                    printf("Game Over\n");
                    return 0;
                }
                else if (table[playerRow - 1][playerCol] == 'C') {
                    printf("Hai trovato la chiave! Hai vinto!\n");
                    return 0;
                }
                else {
                    table[playerRow][playerCol] = ' ';
                    table[--playerRow][playerCol] = 'P';
                }
            }
            break;
        case 'a': // Sinistra
            if (playerCol > 0) {
                if (table[playerRow][playerCol - 1] == 'N') {
                    printf("Game Over\n");
                    return 0;
                }
                else if (table[playerRow][playerCol - 1] == 'C') {
                    printf("Hai trovato la chiave! Hai vinto!\n");
                    return 0;
                }
                else {
                    table[playerRow][playerCol] = ' ';
                    table[playerRow][--playerCol] = 'P';
                }
            }
            break;
        case 's': // Giù
            if (playerRow < ROWS - 1) {
                if (table[playerRow + 1][playerCol] == 'N') {
                    printf("Game Over\n");
                    return 0;
                }
                else if (table[playerRow + 1][playerCol] == 'C') {
                    printf("Hai trovato la chiave! Hai vinto!\n");
                    return 0;
                }
                else {
                    table[playerRow][playerCol] = ' ';
                    table[++playerRow][playerCol] = 'P';
                }
            }
            break;
        case 'd': // Destra
            if (playerCol < COLS - 1) {
                if (table[playerRow][playerCol + 1] == 'N') {
                    printf("Game Over\n");
                    return 0;
                }
                else if (table[playerRow][playerCol + 1] == 'C') {
                    printf("Hai trovato la chiave! Hai vinto!\n");
                    return 0;
                }
                else {
                    table[playerRow][playerCol] = ' ';
                    table[playerRow][++playerCol] = 'P';
                }
            }
            break;
        default:
            printf("Direzione non valida. Riprova.\n");
        }

        // Muovi i nemici
        moveEnemies(table, playerRow, playerCol);

        // Stampa della tabella aggiornata
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

    // Esegui il secondo programma
    system("Livello2.cpp");
}
