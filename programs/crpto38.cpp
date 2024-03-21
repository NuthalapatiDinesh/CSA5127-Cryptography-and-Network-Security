#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MATRIX_SIZE 3 // Size of the key matrix

// Function to encrypt a plaintext using the Hill cipher
void encrypt_hill(const int key[MATRIX_SIZE][MATRIX_SIZE], const char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);
    int blocks = ceil((double)len / MATRIX_SIZE);
    int padding = blocks * MATRIX_SIZE - len;

    // Pad the plaintext if necessary
    char padded_plaintext[blocks * MATRIX_SIZE + 1];
    strcpy(padded_plaintext, plaintext);
    for (int i = 0; i < padding; i++) {
        padded_plaintext[len + i] = 'x'; // Padding with 'x'
    }
    padded_plaintext[len + padding] = '\0';

    // Perform matrix multiplication to encrypt the plaintext
    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += (key[j][k] * (padded_plaintext[i * MATRIX_SIZE + k] - 'a')) % 26;
            }
            ciphertext[i * MATRIX_SIZE + j] = (sum % 26) + 'a';
        }
    }
    ciphertext[blocks * MATRIX_SIZE] = '\0';
}

// Function to decrypt a ciphertext using the Hill cipher
void decrypt_hill(const int key[MATRIX_SIZE][MATRIX_SIZE], const char *ciphertext, char *plaintext) {
    // Calculate the inverse of the key matrix
    int inv_key[MATRIX_SIZE][MATRIX_SIZE];
    int det = key[0][0] * (key[1][1] * key[2][2] - key[1][2] * key[2][1]) -
              key[0][1] * (key[1][0] * key[2][2] - key[1][2] * key[2][0]) +
              key[0][2] * (key[1][0] * key[2][1] - key[1][1] * key[2][0]);

    int det_inv = 0;
    for (int i = 1; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            det_inv = i;
            break;
        }
    }

    inv_key[0][0] = (key[1][1] * key[2][2] - key[1][2] * key[2][1]) * det_inv % 26;
    inv_key[0][1] = (key[0][2] * key[2][1] - key[0][1] * key[2][2]) * det_inv % 26;
    inv_key[0][2] = (key[0][1] * key[1][2] - key[0][2] * key[1][1]) * det_inv % 26;
    inv_key[1][0] = (key[1][2] * key[2][0] - key[1][0] * key[2][2]) * det_inv % 26;
    inv_key[1][1] = (key[0][0] * key[2][2] - key[0][2] * key[2][0]) * det_inv % 26;
    inv_key[1][2] = (key[0][2] * key[1][0] - key[0][0] * key[1][2]) * det_inv % 26;
    inv_key[2][0] = (key[1][0] * key[2][1] - key[1][1] * key[2][0]) * det_inv % 26;
    inv_key[2][1] = (key[0][1] * key[2][0] - key[0][0] * key[2][1]) * det_inv % 26;
    inv_key[2][2] = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) * det_inv % 26;

    // Decrypt the ciphertext using the inverse key matrix
    int len = strlen(ciphertext);
    int blocks = len / MATRIX_SIZE;

    for (int i = 0; i < blocks; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int sum = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                sum += (inv_key[j][k] * (ciphertext[i * MATRIX_SIZE + k] - 'a')) % 26;
            }
            plaintext[i * MATRIX_SIZE + j] = (sum % 26) + 'a';
        }
    }
    plaintext[blocks * MATRIX_SIZE] = '\0';
}

// Function to perform a chosen plaintext attack on the Hill cipher
void chosen_plaintext_attack(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    char known_plaintext[] = "attackatdawn";
    char known_ciphertext[] = "pfhmjxfldvst";
    char plaintext[100];

    decrypt_hill(key, known_ciphertext, plaintext);
    printf("Decrypted ciphertext: %s\n", plaintext);

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            int target = known_plaintext[i] - 'a';
            int source = known_ciphertext[i] - 'a';
            key[j][i] = (source - target + 26) % 26;
        }
    }
}

int main() {
    int key[MATRIX_SIZE][MATRIX_SIZE] = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    // Perform chosen plaintext attack
    chosen_plaintext_attack(key);

    return 0;
}

