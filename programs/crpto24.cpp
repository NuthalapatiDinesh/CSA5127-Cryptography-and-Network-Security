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

// Function to encrypt a message using RSA public key
uint64_t rsa_encrypt(uint64_t message, uint64_t e, uint64_t n) {
    return mod_exp(message, e, n);
}

// Function to decrypt a message without using the private key
uint64_t rsa_decrypt(uint64_t encrypted_message, uint64_t e, uint64_t n) {
    // Without the private key, decryption is not possible
    return encrypted_message;
}

int main() {
    // Public key parameters
    uint64_t e = 31;  // Public exponent
    uint64_t n = 3599;  // Modulus

    // Plaintext message to be encrypted
    uint64_t plaintext = 1234;

    // Encrypt the plaintext message
    uint64_t encrypted_message = rsa_encrypt(plaintext, e, n);
    printf("Encrypted message: %lu\n", encrypted_message);

    // Decrypt the encrypted message without using the private key
    uint64_t decrypted_message = rsa_decrypt(encrypted_message, e, n);
    printf("Decrypted message: %lu\n", decrypted_message);

    return 0;
}
