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

// Diffie-Hellman key exchange function
uint64_t diffie_hellman(uint64_t private_key, uint64_t public_key, uint64_t prime) {
    return mod_exp(public_key, private_key, prime);
}

int main() {
    // Public parameters
    uint64_t prime = 23; // Prime number
    uint64_t generator = 5; // Generator

    // Private keys
    uint64_t alice_private_key = 6; // Alice's private key
    uint64_t bob_private_key = 15; // Bob's private key

    // Compute public keys
    uint64_t alice_public_key = mod_exp(generator, alice_private_key, prime); // Alice's public key
    uint64_t bob_public_key = mod_exp(generator, bob_private_key, prime); // Bob's public key

    // Perform key exchange
    uint64_t alice_shared_secret = diffie_hellman(alice_private_key, bob_public_key, prime); // Alice computes shared secret
    uint64_t bob_shared_secret = diffie_hellman(bob_private_key, alice_public_key, prime); // Bob computes shared secret

    // Print shared secrets
    printf("Alice's shared secret: %llu\n", alice_shared_secret);
    printf("Bob's shared secret: %llu\n", bob_shared_secret);

    return 0;
}
