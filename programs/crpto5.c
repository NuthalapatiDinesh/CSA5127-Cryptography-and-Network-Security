#include <stdio.h>

// Function to find the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to determine if a is coprime with 26
int isCoprime(int a) {
    return gcd(a, 26) == 1;
}

// Function to check if b satisfies the condition
int isValidB(int b) {
    return b % 26 != 0;
}

int main() {
    int a, b;
    printf("Enter values of a and b: ");
    scanf("%d %d", &a, &b);

    if (!isCoprime(a)) {
        printf("Value of a is not allowed. It must be coprime with 26.\n");
    } else if (!isValidB(b)) {
        printf("Value of b is not allowed. It must not be divisible by 26.\n");
    } else {
        printf("Both values of a and b are allowed for the affine Caesar cipher.\n");
    }

    return 0;
}

