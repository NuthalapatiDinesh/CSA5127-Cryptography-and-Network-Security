#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24 
void des_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    memcpy(output, input, BLOCK_SIZE);
}
void add_padding(unsigned char *input, int input_len, int block_size) {
    int padding_len = block_size - (input_len % block_size);
    input[input_len] = 0x80;
    memset(input + input_len + 1, 0, padding_len - 1);
}

void encrypt_ecb(unsigned char *input, int input_len, unsigned char *key) {
    int num_blocks = input_len / BLOCK_SIZE;
    unsigned char *ecb_encrypted = (unsigned char *)malloc(input_len);
    if (ecb_encrypted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }
    for (int i = 0; i < num_blocks; i++) {
        des_encrypt(input + i * BLOCK_SIZE, ecb_encrypted + i * BLOCK_SIZE, key);
    }
    if (input_len % BLOCK_SIZE != 0) {
        add_padding(ecb_encrypted, input_len, BLOCK_SIZE);
    }
    printf("Encrypted data (ECB mode):\n");
    for (int i = 0; i < input_len; i++) {
        printf("%02X ", ecb_encrypted[i]);
    }
    printf("\n");

    // Free allocated memory
    free(ecb_encrypted);
}

int main() {
    unsigned char plaintext[] = "Hello, World!";
    unsigned char key[KEY_SIZE] = "my3DESkey";

    int input_len = strlen((char *)plaintext);
    int padded_len = input_len + (BLOCK_SIZE - (input_len % BLOCK_SIZE)); // Padding the input

    // Encrypt the plaintext using ECB mode and print the encrypted data
    encrypt_ecb(plaintext, padded_len, key);

    return 0;
}
