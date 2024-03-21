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

// Function to generate new public and private keys
void generate_new_keys(uint64_t *e, uint64_t *d, uint64_t phi_n) {
    // Choose a new public exponent e (commonly chosen to be a small prime)
    // In practice, e should be chosen such that gcd(e, phi_n) = 1
    *e = 65537; // Commonly used value for e

    // Calculate the new private exponent d
    // d is the modular multiplicative inverse of e modulo phi_n
    // Use extended Euclidean algorithm to find the multiplicative inverse
    *d = mod_exp(*e, phi_n - 1, phi_n);
}

int main() {
    // Original modulus n and private exponent d (leaked private key)
    uint64_t n = 3599; // Modulus
    uint64_t d = 101;  // Leaked private exponent

    // Calculate Euler's totient function (phi(n)) for the original modulus n
    // phi(n) = (p - 1)(q - 1) for n = p * q, where p and q are prime factors of n
    uint64_t phi_n = n - 1; // If n is a product of two distinct primes, as usual in RSA

    // Generate new public and private keys
    uint64_t e_new, d_new;
    generate_new_keys(&e_new, &d_new, phi_n);

    // Print the new public and private keys
    printf("New public key (e): %lu\n", e_new);
    printf("New private key (d): %lu\n", d_new);

    return 0;
}
