#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size in bytes

// Function to perform CBC encryption
void cbc_encrypt(uint8_t key[], uint8_t plaintext[], uint8_t ciphertext[], uint8_t iv[]) {
    // Encrypt the first block
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ iv[i];
    }

    // Assume simple block cipher (XOR) for demonstration
    for (int i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] ^= key[i];
    }
}

// Function to compute CBC MAC for a one-block message
void cbc_mac(uint8_t key[], uint8_t message[], uint8_t mac[]) {
    uint8_t iv[BLOCK_SIZE] = {0}; // Initialization vector

    // Encrypt the message using CBC mode
    cbc_encrypt(key, message, mac, iv);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    uint8_t message[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    uint8_t mac[BLOCK_SIZE]; // MAC for one-block message
    uint8_t two_block_message[2 * BLOCK_SIZE]; // Two-block message (X || (X ? T))
    uint8_t ciphertext[2 * BLOCK_SIZE]; // Ciphertext for two-block message

    // Compute CBC MAC for the one-block message
    cbc_mac(key, message, mac);

    printf("MAC for one-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac[i]);
    }
    printf("\n");

    // Construct the two-block message (X || (X ? T))
    memcpy(two_block_message, message, BLOCK_SIZE); // Copy X
    for (int i = 0; i < BLOCK_SIZE; i++) {
        two_block_message[BLOCK_SIZE + i] = message[i] ^ mac[i]; // X ? T
    }

    // Encrypt the two-block message using CBC mode
    cbc_encrypt(key, two_block_message, ciphertext, mac);

    printf("MAC for two-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[BLOCK_SIZE + i]); // Last block of ciphertext
    }
    printf("\n");

    return 0;
}
