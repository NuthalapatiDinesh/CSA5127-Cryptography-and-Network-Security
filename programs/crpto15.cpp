#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt plaintext using one-time pad Vigenère cipher
void encrypt(char *plaintext, int *key, int key_length, char *ciphertext) {
    int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % key_length];
            if (islower(plaintext[i]))
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            else
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0';
}

// Function to decrypt ciphertext using one-time pad Vigenère cipher
void decrypt(char *ciphertext, int *key, int key_length, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i % key_length];
            if (islower(ciphertext[i])) {
                int temp = (ciphertext[i] - 'a' - shift) % 26;
                if (temp < 0)
                    temp += 26;
                plaintext[i] = temp + 'a';
            } else {
                int temp = (ciphertext[i] - 'A' - shift) % 26;
                if (temp < 0)
                    temp += 26;
                plaintext[i] = temp + 'A';
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[] = "send more money";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Given key stream
    int key_length = sizeof(key) / sizeof(key[0]);
    char ciphertext[strlen(plaintext) + 1];
    char decrypted_plaintext[strlen(plaintext) + 1];

    // Encrypt the plaintext
    encrypt(plaintext, key, key_length, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext to find the key
    decrypt(ciphertext, key, key_length, decrypted_plaintext);
    printf("Decrypted: %s\n", decrypted_plaintext);

    return 0;
}

