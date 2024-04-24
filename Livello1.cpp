#include <stdlib.h>
#include <string>

int main() {
    char Livello1[10][10] = {0};
    int i = 0;
    int j = 0;

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == 0 || i == 10 - 1) {
                Livello1[i][j] = '_';
            }
            else {
                if (j == 0 || j == 10 - 1) {
                        Livello1[i][j] = '|';
                }
                else {
                    Livello1[i][j] = ' ';
                }
            }
        }
    }

    for (i = 0;i < 10;i++) {
        for (j = 0;j < 10;j++) {
            printf("%c ", Livello1[i][j]);
        }
        printf("\n");
    }

}