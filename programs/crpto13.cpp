#include <stdio.h>
#include <stdlib.h>

#define MOD 26 // Modulus for alphabet (assuming English alphabet)

// Function to find modular inverse of a (mod m)
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // Modular inverse doesn't exist
}

// Function to encrypt a message using Hill Cipher
void hillCipherEncrypt(int key[2][2], char *message, int length) {
    int i, j, k, sum;
    int cipher[length];

    // Convert message to numbers (0-25)
    for (i = 0; i < length; i++) {
        if (message[i] >= 'a' && message[i] <= 'z')
            message[i] -= 'a';
        else if (message[i] >= 'A' && message[i] <= 'Z')
            message[i] -= 'A';
        else {
            // Ignore characters that are not alphabets
            continue;
        }
    }

    // Encrypt the message
    for (i = 0; i < length; i += 2) {
        for (j = 0; j < 2; j++) {
            sum = 0;
            for (k = 0; k < 2; k++) {
                sum += key[j][k] * message[i + k];
            }
            cipher[i + j] = sum % MOD;
        }
    }

    // Print the encrypted message
    printf("Encrypted Message: ");
    for (i = 0; i < length; i++) {
        if (message[i] >= 0 && message[i] <= 25)
            printf("%c", cipher[i] + 'A');
        else
            printf("%c", message[i]);
    }
    printf("\n");
}

// Function to decrypt a message using Hill Cipher
void hillCipherDecrypt(int key[2][2], char *cipher, int length) {
    int i, j, k, sum;
    int invKey[2][2];
    int message[length];

    // Calculate inverse of key
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int invDet = modInverse(det, MOD);
    if (invDet == -1) {
        printf("Inverse doesn't exist!\n");
        return;
    }

    invKey[0][0] = key[1][1];
    invKey[1][1] = key[0][0];
    invKey[0][1] = -key[0][1];
    invKey[1][0] = -key[1][0];

    // Apply modulo
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            invKey[i][j] = (invKey[i][j] * invDet) % MOD;
            if (invKey[i][j] < 0)
                invKey[i][j] += MOD;
        }
    }

    // Decrypt the message
    for (i = 0; i < length; i += 2) {
        for (j = 0; j < 2; j++) {
            sum = 0;
            for (k = 0; k < 2; k++) {
                sum += invKey[j][k] * (cipher[i + k] - 'A');
            }
            message[i + j] = sum % MOD;
        }
    }

    // Print the decrypted message
    printf("Decrypted Message: ");
    for (i = 0; i < length; i++) {
        if (cipher[i] >= 'A' && cipher[i] <= 'Z')
            printf("%c", message[i] + 'a');
        else
            printf("%c", cipher[i]);
    }
    printf("\n");
}

int main() {
    int key[2][2] = {{3, 2}, {5, 7}}; // Example key
    char message[] = "HELLO"; // Example plaintext
    int length = sizeof(message) - 1; // Length of the message

    // Encrypt the message
    hillCipherEncrypt(key, message, length);

    // Decrypt the message
    hillCipherDecrypt(key, message, length);

    return 0;
}

