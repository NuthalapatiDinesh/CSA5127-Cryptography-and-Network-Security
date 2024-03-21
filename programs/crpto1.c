#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void caesarCipher(char *text, int shift);

int main() {
    char text[100];
    int shift;

    printf("Enter text to encrypt: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);

    // Validate the shift value
    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Shift must be between 1 and 25.\n");
        return 1;
    }

    caesarCipher(text, shift);

    printf("Encrypted text: %s\n", text);

    return 0;
}

void caesarCipher(char *text, int shift) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = base + ((text[i] - base + shift) % ALPHABET_SIZE);
        }
    }
}

