#include <stdio.h>
#include <stdlib.h>

#define ROWS 11
#define COLS 8

void printMatrix(char table[ROWS][COLS], int playerRow, int playerCol) {
    printf("\t\t\t\t\t\t\t\t\t\t    U\n");
    printf("\t\t\t\t\tI-------+-------+-------+-------+-------+-------+-------+-------I\n");
    for (int i = 0; i < ROWS; i++) {
        printf("\t\t\t\t\t|   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |   %c   |\n",
            table[i][0], table[i][1], table[i][2], table[i][3],
            table[i][4], table[i][5], table[i][6], table[i][7]);
        if (i == ROWS - 1) {
            printf("\t\t\t\t\t!-------+-------+-------+-------+-------+-------+-------+-------!\n");
        }
        else {
            printf("\t\t\t\t\t|-------+-------+-------+-------+-------+-------+-------+-------|\n");
        }
    }
    printf("\n");
}


void resetGame(char matrix[ROWS][COLS], int* playerRow, int* playerCol, int* prevPlayerRow, int* prevPlayerCol) {
    *playerRow = 10;
    *playerCol = 4;
    *prevPlayerRow = *playerRow;
    *prevPlayerCol = *playerCol;

    // Ripristina la matrice allo stato originale
    char originalMatrix[ROWS][COLS] = {
        {'1', '1', '1', '1', '1', ' ', '1', '1'},
        {'0', '0', '0', '0', '0', '3', '0', '0'},
        {'0', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', ' ', '2', ' ', ' ', '0'},
        {'0', '2', ' ', ' ', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', '2', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', ' ', ' ', ' ', '2', '0'},
        {'0', ' ', '2', ' ', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', ' ', 'S', '2', ' ', '0'},
        {'0', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
        {'0', '0', '0', '0', 'P', '0', '0', '0'}
    };
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matrix[i][j] = originalMatrix[i][j];
        }
    }
    system("cls");
}

int main() {
    char matrix[ROWS][COLS] = {
        {'1', '1', '1', '1', '1', ' ', '1', '1'},
        {'0', '0', '0', '0', '0', '3', '0', '0'},
        {'0', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', ' ', '2', ' ', ' ', '0'},
        {'0', '2', ' ', ' ', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', '2', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', ' ', ' ', ' ', '2', '0'},
        {'0', ' ', '2', ' ', ' ', ' ', ' ', '0'},
        {'0', ' ', ' ', ' ', 'S', '2', ' ', '0'},
        {'0', ' ', ' ', ' ', ' ', ' ', ' ', '0'},
        {'0', '0', '0', '0', 'P', '0', '0', '0'}
    };

    int playerRow = 10;
    int playerCol = 4;
    int prevPlayerRow = playerRow;
    int prevPlayerCol = playerCol;
    int legendPrinted = 0;
    int pianistelloPos[ROWS][COLS] = { 0 };
    char playAgain;
    int helpPart = 1;


    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (matrix[i][j] == '2') {
                pianistelloPos[i][j] = 1;
            }
        }
    }

    char direction;

    while (1) {
        if (!legendPrinted) {
            printf("\nLegenda:\n");
            printf("Muro(1): Rappresenta una parete. Non posso attraversare i muri.\n");
            printf("Vuoto( ): Indica uno spazio libero nel quale posso muovermi senza alcun ostacolo. E' una cella senza alcun tipo di elemento.\n");
            printf("Pianistello(2): Questo elemento potrebbe essere una sorta di piattaforma, su cui posso camminare.\n");
            printf("Buco(3): Rappresenta una lacuna nel terreno. Potrei cadere in un buco se non presto attenzione.\n");
            printf("Sasso(S): E' un oggetto solido che il personaggio puo' spostare. Forse serve a qualcosa?\n");
            printf("Personaggio(P): Il giocatore controlla questo elemento. Puo' muoversi all'interno dell'ambiente e interagire con gli altri elementi.\n");
            printf("Uscita(U): Questo rappresenta il punto di uscita. Bloccato pero' da una lacuna... \n\n\n");
            legendPrinted = 1;
        }

        printMatrix(matrix, playerRow, playerCol);

        printf("\nIn che direzione vuoi muoverti? (w/a/s/d) o se vuoi ricominciare (r) o se vuoi un aiuto (A): ");
        scanf(" %c", &direction);

        prevPlayerRow = playerRow;
        prevPlayerCol = playerCol;

        switch (direction) {
        case 'w':
            // Gestione del movimento verso l'alto
            if (playerRow > 0 && (matrix[playerRow - 1][playerCol] != '0' && matrix[playerRow - 1][playerCol] != '3')) {
                // Se la cella sopra non contiene uno 0 o un 3
                if (matrix[playerRow - 1][playerCol] == ' ') {
                    // Se la cella sopra è vuota, sposta il personaggio
                    playerRow--;
                    if (matrix[prevPlayerRow][prevPlayerCol] == 'S') {
                        // Se la cella precedente del personaggio era un masso, sposta anche il masso
                        matrix[prevPlayerRow][prevPlayerCol] = ' ';
                        matrix[playerRow][playerCol] = 'S';
                    }
                }
                else if (matrix[playerRow - 1][playerCol] == '2') {
                    // Se la cella sopra contiene un "2", sposta il personaggio
                    playerRow--;
                }
                else if (matrix[playerRow - 1][playerCol] == 'S') {
                    // Se la cella sopra contiene un "S" (masso), controlla se può spostarsi
                    int nextRow = playerRow - 1;
                    while (nextRow > 0 && matrix[nextRow - 1][playerCol] == ' ') {
                        // Continua a spostare il masso fino a quando trova uno 0 o una cella vuota sopra di sé
                        matrix[nextRow][playerCol] = ' ';
                        matrix[nextRow - 1][playerCol] = 'S';
                        nextRow--;
                    }
                }
                break;
            }
            else {
                printf("Non puoi muoverti in una cella con un muro (1), un buco (3) o un ostacolo (0).\n");
                break;
            }
        case 'a':
            // Gestione del movimento verso sinistra
            if (playerCol > 0 && (matrix[playerRow][playerCol - 1] != '0' && matrix[playerRow][playerCol - 1] != '3')) {
                // Se la cella a sinistra non contiene uno 0 o un 3
                if (matrix[playerRow][playerCol - 1] == ' ') {
                    // Se la cella a sinistra è vuota, sposta il personaggio
                    playerCol--;
                    if (matrix[prevPlayerRow][prevPlayerCol] == 'S') {
                        // Se la cella precedente del personaggio era un masso, sposta anche il masso
                        matrix[prevPlayerRow][prevPlayerCol] = ' ';
                        matrix[playerRow][playerCol] = 'S';
                    }
                }
                else if (matrix[playerRow][playerCol - 1] == '2') {
                    // Se la cella a sinistra contiene un "2", sposta il personaggio
                    playerCol--;
                }
                else if (matrix[playerRow][playerCol - 1] == 'S') {
                    // Se la cella a sinistra contiene un "S" (masso), controlla se può spostarsi
                    int nextCol = playerCol - 1;
                    while (nextCol > 0 && matrix[playerRow][nextCol - 1] == ' ') {
                        // Continua a spostare il masso fino a quando trova uno 0 o una cella vuota a sinistra
                        matrix[playerRow][nextCol] = ' ';
                        matrix[playerRow][nextCol - 1] = 'S';
                        nextCol--;
                    }
                }
                break;
            }
            else {
                printf("Non puoi muoverti in una cella con un muro (1), un buco (3) o un ostacolo (0).\n");
                break;
            }
        case 's':
            // Gestione del movimento verso il basso
            if (playerRow < ROWS - 1 && (matrix[playerRow + 1][playerCol] != '0' && matrix[playerRow + 1][playerCol] != '3')) {
                // Se la cella sotto non contiene uno 0 o un 3
                if (matrix[playerRow + 1][playerCol] == ' ') {
                    // Se la cella sotto è vuota, sposta il personaggio
                    playerRow++;
                    if (matrix[prevPlayerRow][prevPlayerCol] == 'S') {
                        // Se la cella precedente del personaggio era un masso, sposta anche il masso
                        matrix[prevPlayerRow][prevPlayerCol] = ' ';
                        matrix[playerRow][playerCol] = 'S';
                    }
                }
                else if (matrix[playerRow + 1][playerCol] == '2') {
                    // Se la cella sotto contiene un "2", sposta il personaggio
                    playerRow++;
                }
                else if (matrix[playerRow + 1][playerCol] == 'S') {
                    // Se la cella sotto contiene un "S" (masso), controlla se può spostarsi
                    int nextRow = playerRow + 1;
                    while (nextRow < ROWS - 1 && matrix[nextRow + 1][playerCol] == ' ') {
                        // Continua a spostare il masso fino a quando trova uno 0 o una cella vuota sotto di sé
                        matrix[nextRow][playerCol] = ' ';
                        matrix[nextRow + 1][playerCol] = 'S';
                        nextRow++;
                    }
                }
                break;
            }
            else {
                printf("Non puoi muoverti in una cella con un muro (1), un buco (3) o un ostacolo (0).\n");
                break;
            }
        case 'd':
            // Gestione del movimento verso destra
            if (playerCol < COLS - 1 && (matrix[playerRow][playerCol + 1] != '0' && matrix[playerRow][playerCol + 1] != '3')) {
                // Se la cella a destra non contiene uno 0 o un 3
                if (matrix[playerRow][playerCol + 1] == ' ') {
                    // Se la cella a destra è vuota, sposta il personaggio
                    playerCol++;
                    if (matrix[prevPlayerRow][prevPlayerCol] == 'S') {
                        // Se la cella precedente del personaggio era un masso, sposta anche il masso
                        matrix[prevPlayerRow][prevPlayerCol] = ' ';
                        matrix[playerRow][playerCol] = 'S';
                    }
                }
                else if (matrix[playerRow][playerCol + 1] == '2') {
                    // Se la cella a destra contiene un "2", sposta il personaggio
                    playerCol++;
                }
                else if (matrix[playerRow][playerCol + 1] == 'S') {
                    // Se la cella a destra contiene un "S" (masso), controlla se può spostarsi
                    int nextCol = playerCol + 1;
                    while (nextCol < COLS - 1 && matrix[playerRow][nextCol + 1] == ' ') {
                        // Continua a spostare il masso fino a quando trova uno 0 o una cella vuota a destra
                        matrix[playerRow][nextCol] = ' ';
                        matrix[playerRow][nextCol + 1] = 'S';
                        nextCol++;
                    }
                }
                break;
            }
            else {
                printf("Non puoi muoverti in una cella con un muro (1), un buco (3) o un ostacolo (0).\n");
                break;
            }
        case 'r':
            // Richiedi all'utente se vuole ricominciare la partita
            printf("Vuoi ricominciare la partita? (s/n): ");
            scanf(" %c", &playAgain);
            if (playAgain == 's' || playAgain == 'S') {
                resetGame(matrix, &playerRow, &playerCol, &prevPlayerRow, &prevPlayerCol);
                legendPrinted = 0;
                continue;
            }
            else {
                printf("Fine del gioco. Arrivederci!\n");
                return 0;
            }
        case 'A':
            switch (helpPart) {
            case 1:
                printf("\nParte 1 dell'aiuto: Questo enigma non dovrebbe essere troppo complicato forse la roccia potrebbe bloccare quel buco e potrei arrivare all'uscita?.\n");
                break;
            case 2:
                printf("\nParte 2 dell'aiuto: Muovi la roccia in avanti premento \"w\" nella riga sotto di esso avra' un comportamento particolare.\n");
                break;
            case 3:
                printf("\nParte 3 dell'aiuto: La roccia su puo' muovere in tutte le direzioni proprio come il personaggio.\n");
                break;
            case 4:
                printf("\nParte 4 dell'aiuto: Muovi la roccia verso il sinistra e poi verso il basso direi che ora la soluzione dell'enigma sara' chiara.\n");
                break;
            default:
                printf("\nNon ci sono più parti di aiuto disponibili.\n");
                break;
            }
            helpPart = (helpPart % 4) + 1; // Passa alla parte successiva dell'aiuto
            continue;
        default:
            printf("Direzione non valida. Riprova.\n");
            continue;
        }

        if (matrix[2][5] == 'S') {
            matrix[2][5] = ' ';
            matrix[1][5] = ' ';
        }
        if (matrix[10][4] == 'S') {
            printMatrix(matrix, playerRow, playerCol);
            printf("Ma quanto sono stupido da bloccami l'uscita...");
            break;
        }

        // se il masso va in una posizione vicino allo 0 cioè vuoto

        if (matrix[2][1] == 'S' || matrix[2][2] == 'S' || matrix[2][3] == 'S' || matrix[2][4] == 'S' || matrix[2][6] == 'S' || matrix[3][1] == 'S' || matrix[3][6] == 'S' || matrix[4][6] == 'S' || matrix[5][1] == 'S' || matrix[5][6] == 'S' || matrix[6][1] == 'S' || matrix[7][1] == 'S' || matrix[7][6] == 'S' || matrix[8][1] == 'S' || matrix[8][6] == 'S' || matrix[9][1] == 'S' || matrix[9][2] == 'S' || matrix[9][3] == 'S' || matrix[9][5] == 'S' || matrix[9][6] == 'S') {
            matrix[2][1] = ' ';
            matrix[2][2] = ' ';
            matrix[2][3] = ' ';
            matrix[2][4] = ' ';
            matrix[2][6] = ' ';
            matrix[3][1] = ' ';
            matrix[3][6] = ' ';
            matrix[4][6] = ' ';
            matrix[5][1] = ' ';
            matrix[5][6] = ' ';
            matrix[6][1] = ' ';
            matrix[7][1] = ' ';
            matrix[7][6] = ' ';
            matrix[8][1] = ' ';
            matrix[8][6] = ' ';
            matrix[9][1] = ' ';
            matrix[9][2] = ' ';
            matrix[9][3] = ' ';
            matrix[9][5] = ' ';
            matrix[9][6] = ' ';
            printMatrix(matrix, playerRow, playerCol);
            printf("Vuoi ricominciare la partita? (s/n): ");
            scanf(" %c", &playAgain);
            if (playAgain == 's' || playAgain == 'S') {
                resetGame(matrix, &playerRow, &playerCol, &prevPlayerRow, &prevPlayerCol);
                legendPrinted = 0;
                continue;
            }
            else {
                printf("Fine del gioco. Arrivederci!\n");
                break;
            }
        }

        if (playerRow < 0 || playerRow >= ROWS || playerCol < 0 || playerCol >= COLS) {
            printf("Movimento non consentito. Riprova.\n");
            playerRow = prevPlayerRow;
            playerCol = prevPlayerCol;
            continue;
        }

        if (matrix[playerRow][playerCol] == '0') {
            printf("Non puoi muoverti attraverso muri, buchi!\n");
            playerRow = prevPlayerRow;
            playerCol = prevPlayerCol;
            continue;
        }

        if (pianistelloPos[prevPlayerRow][prevPlayerCol] == 1) {
            matrix[prevPlayerRow][prevPlayerCol] = '2';
        }
        else {
            matrix[prevPlayerRow][prevPlayerCol] = ' ';
        }
        matrix[playerRow][playerCol] = 'P';


        if (playerRow == 0 && playerCol == 5) {
            printMatrix(matrix, playerRow, playerCol);
            printf("\nHai raggiunto la posizione finale! Fine del gioco.\n");
            break;
        }
    }
}
