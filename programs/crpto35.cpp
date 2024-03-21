#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Function to encrypt plaintext using the one-time pad Vigenère cipher
void encrypt_vigenere(const char *plaintext, const int *key, int key_len, char *ciphertext) {
    int i, j;
    for (i = 0, j = 0; plaintext[i] != '\0'; i++, j = (j + 1) % key_len) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            // Encrypt the current character using the key
            ciphertext[i] = ((plaintext[i] - base + key[j]) % 26) + base;
        } else {
            ciphertext[i] = plaintext[i]; // Leave non-alphabetic characters unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext string
}

int main() {
    const char *plaintext = "Hello, World!";
    const int key[] = {3, 19, 5}; // Example key
    const int key_len = sizeof(key) / sizeof(key[0]);

    char ciphertext[100]; // Allocate enough space for the ciphertext

    // Encrypt the plaintext using the one-time pad Vigenère cipher
    encrypt_vigenere(plaintext, key, key_len, ciphertext);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Key: ");
    for (int i = 0; i < key_len; i++) {
        printf("%d ", key[i]);
    }
    printf("\n");
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

