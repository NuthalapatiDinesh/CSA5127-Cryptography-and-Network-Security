#include <stdio.h>
#include <stdint.h>

// Function to perform left shift on a 64-bit value
uint64_t left_shift(uint64_t value) {
    return (value << 1) | ((value >> 63) & 0x01);
}

// Function to generate subkeys for CMAC with block size of 64 bits
void generate_subkeys_64(uint64_t *subkey1, uint64_t *subkey2) {
    *subkey1 = left_shift(*subkey1);
    if ((*subkey1 >> 63) & 0x01) {
        *subkey1 ^= 0x1B;
    }
    *subkey2 = left_shift(*subkey1);
    if ((*subkey2 >> 63) & 0x01) {
        *subkey2 ^= 0x1B;
    }
}

// Function to perform left shift on a 128-bit value
__uint128_t left_shift_128(__uint128_t value) {
    return (value << 1) | ((value >> 127) & 0x01);
}

// Function to generate subkeys for CMAC with block size of 128 bits
void generate_subkeys_128(__uint128_t *subkey1, __uint128_t *subkey2) {
    *subkey1 = left_shift_128(*subkey1);
    if ((*subkey1 >> 127) & 0x01) {
        *subkey1 ^= 0x87;
    }
    *subkey2 = left_shift_128(*subkey1);
    if ((*subkey2 >> 127) & 0x01) {
        *subkey2 ^= 0x87;
    }
}

int main() {
    // Constants for block sizes of 64 and 128 bits
    uint64_t subkey64_1 = 0x00;
    uint64_t subkey64_2 = 0x00;
    __uint128_t subkey128_1 = 0x00;
    __uint128_t subkey128_2 = 0x00;

    // Generate subkeys for block size of 64 bits
    generate_subkeys_64(&subkey64_1, &subkey64_2);
    printf("Subkey 1 (64 bits): 0x%016lX\n", subkey64_1);
    printf("Subkey 2 (64 bits): 0x%016lX\n", subkey64_2);

    // Generate subkeys for block size of 128 bits
    generate_subkeys_128(&subkey128_1, &subkey128_2);
    printf("Subkey 1 (128 bits): 0x%032lX%032lX\n", (uint64_t)(subkey128_1 >> 64), (uint64_t)subkey128_1);
    printf("Subkey 2 (128 bits): 0x%032lX%032lX\n", (uint64_t)(subkey128_2 >> 64), (uint64_t)subkey128_2);

    return 0;
}
