#include <stdio.h>

// Function to find the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular inverse using the extended Euclidean algorithm
int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        // q is quotient
        q = a / m;

        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0)
        x1 += m0;

    return x1;
}

int main() {
    int e = 31; // Public exponent
    int n = 3599; // Modulus

    // Step 1: Trial and error to find p and q
    int p, q;
    for (p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            q = n / p;
            break;
        }
    }

    // Step 2: Calculate phi(n)
    int phi_n = (p - 1) * (q - 1);

    // Step 3: Calculate the modular inverse of e modulo phi(n)
    int d = mod_inverse(e, phi_n);

    printf("Private exponent (d): %d\n", d);

    return 0;
}
