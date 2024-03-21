#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000

// Function to remove spaces from the text
void removeSpaces(char* text) {
    int count = 0;
    for (int i = 0; text[i]; i++) {
        if (text[i] != ' ')
            text[count++] = text[i];
    }
    text[count] = '\0';
}

// Function to decrypt Playfair cipher
void decryptPlayfair(char* ciphertext, char key[5][5]) {
    int i, j;
    char a, b;
    int r1, r2, c1, c2;

    for (i = 0; i < strlen(ciphertext); i += 2) {
        a = ciphertext[i];
        b = ciphertext[i + 1];
        // Find positions of characters in the key matrix
        for (j = 0; j < 5; j++) {
            if (strchr(key[j], a) != NULL) {
                r1 = j;
                c1 = strchr(key[j], a) - key[j];
            }
            if (strchr(key[j], b) != NULL) {
                r2 = j;
                c2 = strchr(key[j], b) - key[j];
            }
        }
        // Case 1: Both characters are in the same row
        if (r1 == r2) {
            printf("%c%c", key[r1][(c1 + 4) % 5], key[r2][(c2 + 4) % 5]);
        }
        // Case 2: Both characters are in the same column
        else if (c1 == c2) {
            printf("%c%c", key[(r1 + 4) % 5][c1], key[(r2 + 4) % 5][c2]);
        }
        // Case 3: Forming rectangle, take corners
        else {
            printf("%c%c", key[r1][c2], key[r2][c1]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    strcpy(ciphertext, "KXJEY UREBE ZWEHE WRYTU HEYFS KREHE GOYFI WTTTU OLKSY CAJPO BOTEI ZONTX BYBNT GONEY CUZWR GDSON SXBOU YWRHE BAAHY USEDQ");

    removeSpaces(ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    char key[5][5] = {
        {'A', 'B', 'C', 'D', 'E'},
        {'F', 'G', 'H', 'I', 'K'},
        {'L', 'M', 'N', 'O', 'P'},
        {'Q', 'R', 'S', 'T', 'U'},
        {'V', 'W', 'X', 'Y', 'Z'}
    };

    printf("Possible plaintexts:\n");
    decryptPlayfair(ciphertext, key);

    return 0;
}

