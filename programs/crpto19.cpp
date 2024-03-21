#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24
void des_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    memcpy(output, input, BLOCK_SIZE);
}
void triple_des_encrypt(unsigned char *input, unsigned char *output, unsigned char *key, unsigned char *iv) {
    unsigned char temp_output[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        input[i] ^= iv[i];
    }
    des_encrypt(input, temp_output, key);
    des_encrypt(temp_output, output, key + BLOCK_SIZE);
    des_encrypt(output, temp_output, key + 2 * BLOCK_SIZE);
    memcpy(output, temp_output, BLOCK_SIZE);
}
void encrypt_cbc_3des(unsigned char *input, int input_len, unsigned char *key, unsigned char *iv) {
    unsigned char feedback[BLOCK_SIZE];
    for (int i = 0; i < input_len; i += BLOCK_SIZE) {
        triple_des_encrypt(input + i, input + i, key, iv);
        memcpy(iv, input + i, BLOCK_SIZE);
    }
}

int main() {
    unsigned char plaintext[] = "Hello, World!";
    unsigned char key[KEY_SIZE] = "my3DESkey";
unsigned char iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};


    int input_len = strlen((char *)plaintext);
    int padded_len = input_len + (BLOCK_SIZE - (input_len % BLOCK_SIZE));

    unsigned char *encrypted = (unsigned char *)malloc(padded_len);
    if (encrypted == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    memcpy(encrypted, plaintext, input_len);
    memset(encrypted + input_len, 0, padded_len - input_len);
    encrypt_cbc_3des(encrypted, padded_len, key, iv);
    printf("Encrypted message (hex): ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02X ", encrypted[i]);
    }
    printf("\n");
    free(encrypted);

    return 0;
}
