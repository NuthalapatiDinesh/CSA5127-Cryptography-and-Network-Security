#include <stdio.h>
#include <stdint.h>

// Define a struct to represent 128-bit integers
typedef struct {
    uint64_t low;
    uint64_t high;
} uint128_t;

// Function to perform left shift on a 128-bit value
uint128_t left_shift_128(uint128_t value) {
    uint128_t result;
    result.low = (value.low << 1) | ((value.high >> 63) & 0x01);
    result.high = value.high << 1;
    return result;
}

// Function to generate subkeys for CMAC with block size of 128 bits
void generate_subkeys_128(uint128_t *subkey1, uint128_t *subkey2) {
    *subkey1 = left_shift_128(*subkey1);
    if ((subkey1->high >> 63) & 0x01) {
        subkey1->low ^= 0x87;
    }
    *subkey2 = left_shift_128(*subkey1);
    if ((subkey2->high >> 63) & 0x01) {
        subkey2->low ^= 0x87;
    }
}

int main() {
    // Constants for block sizes of 128 bits
    uint128_t subkey128_1 = {0x00, 0x00};
    uint128_t subkey128_2 = {0x00, 0x00};

    // Generate subkeys for block size of 128 bits
    generate_subkeys_128(&subkey128_1, &subkey128_2);
    printf("Subkey 1 (128 bits): 0x%016lX%016lX\n", subkey128_1.high, subkey128_1.low);
    printf("Subkey 2 (128 bits): 0x%016lX%016lX\n", subkey128_2.high, subkey128_2.low);

    return 0;
}

