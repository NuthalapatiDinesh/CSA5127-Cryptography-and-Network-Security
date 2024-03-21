#include <stdio.h>
#include <stdint.h>

// Function to perform modular exponentiation
uint64_t mod_exp(uint64_t base, uint64_t exponent, uint64_t modulus) {
    uint64_t result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Encrypt a single character using RSA with large modulus and exponent
uint64_t rsa_encrypt(uint64_t plaintext, uint64_t e, uint64_t n) {
    return mod_exp(plaintext, e, n);
}

int main() {
    // Alice's message
    char message[] = "HELLO";

    // Public key parameters (large modulus and exponent)
    uint64_t e = 65537;  // Common public exponent
    uint64_t n = 204524743;  // Large modulus

    // Encrypt each character separately
    printf("Encrypted message: ");
    for (int i = 0; message[i] != '\0'; i++) {
        if (message[i] >= 'A' && message[i] <= 'Z') {
            uint64_t plaintext = message[i] - 'A'; // Map 'A' to 0, 'B' to 1, ..., 'Z' to 25
            uint64_t ciphertext = rsa_encrypt(plaintext, e, n);
            printf("%llu ", ciphertext); // Print encrypted character
        } else {
            // Skip non-alphabetic characters
            printf("%c", message[i]);
        }
    }
    printf("\n");

    return 0;
}
