#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 2

// Function to calculate the determinant of a 2x2 matrix
int determinant(int key[SIZE][SIZE]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

// Function to calculate the modular inverse of a number
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to calculate the adjoint of a 2x2 matrix
void adjoint(int key[SIZE][SIZE], int adj[SIZE][SIZE]) {
    adj[0][0] = key[1][1];
    adj[0][1] = -key[0][1];
    adj[1][0] = -key[1][0];
    adj[1][1] = key[0][0];
}

// Function to calculate the inverse of a 2x2 matrix
void inverse(int key[SIZE][SIZE], int inv[SIZE][SIZE]) {
    int det = determinant(key);
    int inv_det = modInverse(det, 26);

    int adj[SIZE][SIZE];
    adjoint(key, adj);

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            inv[i][j] = adj[i][j] * inv_det;
            while (inv[i][j] < 0)
                inv[i][j] += 26;
            inv[i][j] %= 26;
        }
    }
}

// Function to encrypt the message using the Hill cipher
void encrypt(char *message, int key[SIZE][SIZE]) {
    int len = strlen(message);
    int encrypted[len];

    for (int i = 0; i < len; i += 2) {
        int plain_text[SIZE] = {message[i] - 'a', message[i + 1] - 'a'};
        int cipher_text[SIZE] = {0};

        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                cipher_text[j] += key[j][k] * plain_text[k];
                cipher_text[j] %= 26;
            }
        }

        encrypted[i] = cipher_text[0] + 'a';
        encrypted[i + 1] = cipher_text[1] + 'a';
    }

    encrypted[len] = '\0';

    printf("Encrypted message: %s\n", encrypted);
}

// Function to decrypt the ciphertext using the Hill cipher
void decrypt(char *message, int key[SIZE][SIZE]) {
    int len = strlen(message);
    int decrypted[len];

    int inv[SIZE][SIZE];
    inverse(key, inv);

    for (int i = 0; i < len; i += 2) {
        int cipher_text[SIZE] = {message[i] - 'a', message[i + 1] - 'a'};
        int plain_text[SIZE] = {0};

        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                plain_text[j] += inv[j][k] * cipher_text[k];
                plain_text[j] %= 26;
            }
        }

        decrypted[i] = plain_text[0] + 'a';
        decrypted[i + 1] = plain_text[1] + 'a';
    }

    decrypted[len] = '\0';

    printf("Decrypted message: %s\n", decrypted);
}

int main() {
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";

    int key[SIZE][SIZE] = {
        {9, 4},
        {5, 7}
    };

    printf("Original message: %s\n", message);

    encrypt(message, key);
    decrypt(message, key);

    return 0;
}

