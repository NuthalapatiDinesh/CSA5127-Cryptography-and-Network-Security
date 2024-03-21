#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000

// Function to remove spaces and punctuation from the text
void removeSpacesAndPunctuation(char* text) {
    int count = 0;
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            text[count++] = toupper(text[i]);
        }
    }
    text[count] = '\0';
}

// Function to prepare the plaintext for encryption
void preparePlaintext(char* plaintext) {
    removeSpacesAndPunctuation(plaintext);
    int len = strlen(plaintext);
    // Insert an 'X' between consecutive identical letters
    for (int i = 0; i < len - 1; i += 2) {
        if (plaintext[i] == plaintext[i + 1]) {
            memmove(&plaintext[i + 1], &plaintext[i], len - i);
            plaintext[i + 1] = 'X';
            len++;
        }
    }
    // If the length of the plaintext is odd, append an 'X' at the end
    if (len % 2 != 0) {
        plaintext[len] = 'X';
        plaintext[len + 1] = '\0';
    }
}

// Function to find the position of a character in the key matrix
void findPosition(char key[5][5], char ch, int* row, int* col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (key[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt plaintext using Playfair cipher
void encryptPlayfair(char* plaintext, char key[5][5]) {
    int len = strlen(plaintext);
    int row1, col1, row2, col2;

    for (int i = 0; i < len; i += 2) {
        // Find positions of characters in the key matrix
        findPosition(key, plaintext[i], &row1, &col1);
        findPosition(key, plaintext[i + 1], &row2, &col2);

        // Same row, replace with characters to the right (circular)
        if (row1 == row2) {
            printf("%c%c", key[row1][(col1 + 1) % 5], key[row2][(col2 + 1) % 5]);
        }
        // Same column, replace with characters below (circular)
        else if (col1 == col2) {
            printf("%c%c", key[(row1 + 1) % 5][col1], key[(row2 + 1) % 5][col2]);
        }
        // Forming rectangle, take opposite corners
        else {
            printf("%c%c", key[row1][col2], key[row2][col1]);
        }
    }
    printf("\n");
}

int main() {
    char plaintext[MAX_TEXT_LENGTH] = "Must see you over Cadogan West. Coming at once.";
    char key[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    preparePlaintext(plaintext);

    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: ");
    encryptPlayfair(plaintext, key);

    return 0;
}

