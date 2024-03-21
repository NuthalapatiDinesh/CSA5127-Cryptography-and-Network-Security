#include <stdio.h>
#include <string.h> // Include for memcpy function

// Simplified DES S-boxes
const int sbox[2][4][4] = {
    {
        {1, 0, 3, 2},
        {3, 2, 1, 0},
        {0, 2, 1, 3},
        {3, 1, 3, 2}
    },
    {
        {0, 1, 2, 3},
        {2, 0, 1, 3},
        {3, 0, 1, 0},
        {2, 1, 0, 3}
    }
};

// Initial Permutation (IP) table
const int ip[] = {1, 5, 2, 0, 3, 7, 4, 6};

// Final Permutation (FP) table
const int fp[] = {3, 0, 2, 4, 6, 1, 7, 5};

// Expansion Permutation (EP) table
const int ep[] = {3, 0, 1, 2, 1, 2, 3, 0};

// P4 permutation table
const int p4[] = {1, 3, 2, 0};

// P8 permutation table
const int p8[] = {5, 2, 6, 3, 7, 4, 9, 8};

// Key generation function for S-DES
void generate_keys(int key[], int k1[], int k2[]) {
    // Perform P8 permutation
    int temp_key[8];
    for (int i = 0; i < 8; i++) {
        temp_key[i] = key[p8[i]];
    }

    // Left shift by 1 bit
    int temp = temp_key[0];
    for (int i = 0; i < 7; i++) {
        temp_key[i] = temp_key[i + 1];
    }
    temp_key[7] = temp;

    // Split into left and right halves
    int left[4], right[4];
    for (int i = 0; i < 4; i++) {
        left[i] = temp_key[i];
        right[i] = temp_key[i + 4];
    }

    // Perform P4 permutation to generate K1
    for (int i = 0; i < 4; i++) {
        k1[i] = left[p4[i]];
        k1[i + 4] = right[p4[i]];
    }

    // Left shift by 2 bits
    for (int i = 0; i < 2; i++) {
        temp = left[0];
        for (int j = 0; j < 3; j++) {
            left[j] = left[j + 1];
            right[j] = right[j + 1];
        }
        left[3] = temp;
        right[3] = temp;
    }

    // Perform P4 permutation to generate K2
    for (int i = 0; i < 4; i++) {
        k2[i] = left[p4[i]];
        k2[i + 4] = right[p4[i]];
    }
}

// XOR operation on two arrays
void xor_operation(int a[], int b[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}

// Apply a permutation table
void permutation(int input[], int output[], const int perm[], int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input[perm[i]];
    }
}

// Apply the S-box substitution
void sbox_substitution(int input[], int output[]) {
    int row = (input[0] << 1) + input[3];
    int col = (input[1] << 1) + input[2];
    int val = sbox[0][row][col];
    output[0] = val >> 1;
    output[1] = val & 1;
}

// Perform the F function
void f_function(int r[], int key[], int result[]) {
    int expanded_r[8], xor_result[8], sbox_result[4], perm_result[4];
    // Expand the input to 8 bits
    permutation(r, expanded_r, ep, 8);
    // XOR with the key
    xor_operation(expanded_r, key, xor_result, 8);
    // Apply S-box substitution
    sbox_substitution(xor_result, sbox_result);
    // Permute the result
    permutation(sbox_result, perm_result, p4, 4);
    // Final result
    xor_operation(perm_result, r, result, 4);
}

// Encrypt a 4-bit block
void encrypt_block(int plaintext[], int key[], int ciphertext[]) {
    int ip_result[8], left[4], right[4], temp[4], k1[8], k2[8];

    // Perform the initial permutation (IP)
    permutation(plaintext, ip_result, ip, 8);

    // Split into left and right halves
    for (int i = 0; i < 4; i++) {
        left[i] = ip_result[i];
        right[i] = ip_result[i + 4];
    }

    // Generate subkeys
    generate_keys(key, k1, k2);

    // Perform 2 rounds of Feistel network
    int f_result[4];
    f_function(right, k1, f_result);
    xor_operation(f_result, left, temp, 4);
    memcpy(left, right, sizeof(right));
    memcpy(right, temp, sizeof(temp));

    f_function(right, k2, f_result);
    xor_operation(f_result, left, temp, 4);
    memcpy(left, temp, sizeof(temp));

    // Combine left and right halves
    memcpy(ip_result, left, sizeof(left));
    memcpy(ip_result + 4, right, sizeof(right));

    // Perform the final permutation (FP)
    permutation(ip_result, ciphertext, fp, 8);
}

// Decrypt a 4-bit block
void decrypt_block(int ciphertext[], int key[], int plaintext[]) {
    // In S-DES, encryption and decryption are the same operation
    encrypt_block(ciphertext, key, plaintext);
}

// Convert binary string to integer array
void binary_to_array(const char *binary, int array[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = binary[i] - '0';
    }
}

// Convert integer array to binary string
void array_to_binary(int array[], char *binary, int size) {
    for (int i = 0; i < size; i++) {
        binary[i] = array[i] + '0';
    }
    binary[size] = '\0';
}

int main() {
    int plaintext[8], key[8], iv[8], ciphertext[8], decrypted[8];
    const char *binary_plaintext = "0000000100100011";
    const char *binary_key = "0111111101";
    const char *binary_iv = "10101010";

    // Convert binary strings to integer arrays
    binary_to_array(binary_plaintext, plaintext, 8);
    binary_to_array(binary_key, key, 10); // 10 bits key for S-DES
    binary_to_array(binary_iv, iv, 8);

    // Encryption
    printf("Encryption:\n");
    encrypt_block(plaintext, key, ciphertext);
    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    // Decryption
    printf("\nDecryption:\n");
    decrypt_block(ciphertext, key, decrypted);
    printf("Decrypted plaintext: ");
    for (int i = 0; i < 8; i++) {
        printf("%d", decrypted[i]);
    }
    printf("\n");

    return 0;
}
