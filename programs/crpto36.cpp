#include <stdio.h>
#include <ctype.h>

// Function to encrypt a character using the affine Caesar cipher
char encrypt_char(int a, int b, char plaintext) {
    if (!isalpha(plaintext)) {
        return plaintext; // If the character is not a letter, return it unchanged
    }

    char base = isupper(plaintext) ? 'A' : 'a';
    int x = plaintext - base; // Convert character to a number between 0 and 25

    // Encrypt the character using the formula: C = (a * p + b) mod 26
    int encrypted_char = (a * x + b) % 26;
    if (encrypted_char < 0) {
        encrypted_char += 26; // Ensure the result is positive
    }

    return base + encrypted_char; // Convert the number back to a character and return
}

// Function to encrypt a string using the affine Caesar cipher
void encrypt_affine_caesar(int a, int b, const char *plaintext, char *ciphertext) {
    int i = 0;
    while (plaintext[i] != '\0') {
        ciphertext[i] = encrypt_char(a, b, plaintext[i]);
        i++;
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext string
}

int main() {
    int a = 5; // Value of 'a' in the affine Caesar cipher
    int b = 8; // Value of 'b' in the affine Caesar cipher

    const char *plaintext = "Hello, World!"; // Example plaintext
    char ciphertext[100]; // Allocate enough space for the ciphertext

    // Encrypt the plaintext using the affine Caesar cipher
    encrypt_affine_caesar(a, b, plaintext, ciphertext);

    // Print the results
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

