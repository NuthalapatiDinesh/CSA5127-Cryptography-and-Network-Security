#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24
void des_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    memcpy(output, input, BLOCK_SIZE);
}
void triple_des_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    unsigned char temp_output[BLOCK_SIZE];


    des_encrypt(input, temp_output, key);

    des_encrypt(temp_output, output, key + BLOCK_SIZE);

    des_encrypt(output, temp_output, key + 2 * BLOCK_SIZE);

    memcpy(output, temp_output, BLOCK_SIZE);
}

void encrypt_cbc_3des(unsigned char *input, int input_len, unsigned char *key, unsigned char *iv) {
    unsigned char feedback[BLOCK_SIZE];
    unsigned char temp_block[BLOCK_SIZE];

    memcpy(feedback, iv, BLOCK_SIZE);
    for (int i = 0; i < input_len; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            input[i + j] ^= feedback[j];
        }
        triple_des_encrypt(input + i, temp_block, key);

        // Copy the encrypted block to the output and update the feedback
        memcpy(feedback, temp_block, BLOCK_SIZE);
        memcpy(input + i, temp_block, BLOCK_SIZE);
    }
}

int main() {
    unsigned char input[] = "Hello, World!";
    unsigned char key[KEY_SIZE] = "my3DESkey";
    unsigned char iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF}; // Initialization Vector (IV)

    int input_len = strlen((char *)input);
    int padded_len = input_len + (BLOCK_SIZE - (input_len % BLOCK_SIZE)); // Padding the input

unsigned char *padded_input = (unsigned char *)malloc(padded_len);

    memcpy(padded_input, input, input_len);
    memset(padded_input + input_len, 0, padded_len - input_len); // Padding with zeros

    encrypt_cbc_3des(padded_input, padded_len, key, iv);

    printf("Encrypted message (hex): ");
    for (int i = 0; i < padded_len; i++) {
        printf("%02X ", padded_input[i]);
    }
    printf("\n");

    free(padded_input);
    return 0;
}
