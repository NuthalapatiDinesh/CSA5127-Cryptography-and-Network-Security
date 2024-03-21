#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000

// Function to find the greatest common divisor
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find the modular multiplicative inverse
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return -1;
}

// Function to decrypt the affine cipher
void decryptAffineCipher(char *ciphertext, int a, int b) {
    int m = 26; // Size of the English alphabet
    int a_inverse = modInverse(a, m);

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            int c = ciphertext[i] - 'A';
            int plain = (a_inverse * (c - b + m)) % m;
            plain = (plain + m) % m; // Ensure positive result
            printf("%c", plain + 'A');
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    // Count frequency of each letter
    int freq[26] = {0};
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
        }
    }

    // Find the most frequent and second most frequent letters
    int maxFreq = 0, secondMaxFreq = 0;
    char maxChar, secondMaxChar;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) {
            secondMaxFreq = maxFreq;
            secondMaxChar = maxChar;
            maxFreq = freq[i];
            maxChar = 'A' + i;
        } else if (freq[i] > secondMaxFreq) {
            secondMaxFreq = freq[i];
            secondMaxChar = 'A' + i;
        }
    }

    // Determine key values using the most frequent and second most frequent letters
    int a, b;
    int m = 26; // Size of the English alphabet
    int x1 = maxChar - 'A';
    int x2 = secondMaxChar - 'A';
    int y1 = 'B' - 'A'; // Most frequent letter in English
    int y2 = 'U' - 'A'; // Second most frequent letter in English

    // Solve simultaneous equations to find a and b
    // a * x1 + b = y1 (mod m)
    // a * x2 + b = y2 (mod m)
    // Using substitution method to solve the equations
    for (a = 1; a < m; a++) {
        if ((a * (x1 - x2)) % m == ((y1 - y2) + m) % m) {
            b = (y1 - a * x1 + m) % m;
            break;
        }
    }

    printf("Most frequent letter in the ciphertext: %c\n", maxChar);
    printf("Second most frequent letter in the ciphertext: %c\n", secondMaxChar);
    printf("Key values (a, b) determined: (%d, %d)\n", a, b);

    printf("Decrypted plaintext:\n");
    decryptAffineCipher(ciphertext, a, b);

    return 0;
}

