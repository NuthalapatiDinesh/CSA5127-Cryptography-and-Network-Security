#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void encrypt(char *message, char *key);

int main() {
    char message[1000];
    char key[26];

    // Get input message from the user
    printf("Enter a message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    // Get the substitution key from the user
    printf("Enter the substitution key (26 unique letters): ");
    fgets(key, sizeof(key), stdin);

    // Encrypt the message
    encrypt(message, key);

    printf("\nEncrypted message: %s\n", message);

    return 0;
}

void encrypt(char *message, char *key) {
    int i = 0;
    while (message[i] != '\0') {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = key[message[i] - base];
        }
        i++;
    }
}
