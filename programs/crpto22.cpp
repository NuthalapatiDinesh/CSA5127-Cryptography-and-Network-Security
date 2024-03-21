#include <stdio.h>
#include <string.h>
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
const int ip[] = {1, 5, 2, 0, 3, 7, 4, 6};
const int fp[] = {3, 0, 2, 4, 6, 1, 7, 5};
const int ep[] = {3, 0, 1, 2, 1, 2, 3, 0};
const int p4[] = {1, 3, 2, 0};
const int p8[] = {5, 2, 6, 3, 7, 4, 9, 8};
void generate_keys(int key[], int k1[], int k2[]) {
    int temp_key[8];
    for (int i = 0; i < 8; i++) {
        temp_key[i] = key[p8[i]];
    }
    int temp = temp_key[0];
    for (int i = 0; i < 7; i++) {
        temp_key[i] = temp_key[i + 1];
    }
    temp_key[7] = temp;
    int left[4], right[4];
    for (int i = 0; i < 4; i++) {
        left[i] = temp_key[i];
        right[i] = temp_key[i + 4];
    }
    for (int i = 0; i < 4; i++) {
        k1[i] = left[p4[i]];
        k1[i + 4] = right[p4[i]];
    }
    for (int i = 0; i < 2; i++) {
        temp = left[0];
        for (int j = 0; j < 3; j++) {
            left[j] = left[j + 1];
            right[j] = right[j + 1];
        }
        left[3] = temp;
        right[3] = temp;
    }
    for (int i = 0; i < 4; i++) {
        k2[i] = left[p4[i]];
        k2[i + 4] = right[p4[i]];
    }
}
void xor_operation(int a[], int b[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void permutation(int input[], int output[], const int perm[], int size) {
    for (int i = 0; i < size; i++) {
        output[i] = input[perm[i]];
    }
}
void sbox_substitution(int input[], int output[]) {
    int row = (input[0] << 1) + input[3];
    int col = (input[1] << 1) + input[2];
    int val = sbox[0][row][col];
    output[0] = val >> 1;
    output[1] = val & 1;
}
void f_function(int r[], int key[], int result[]) {
    int expanded_r[8], xor_result[8], sbox_result[4], perm_result[4];
    permutation(r, expanded_r, ep, 8);
    xor_operation(expanded_r, key, xor_result, 8);
    sbox_substitution(xor_result, sbox_result);
    permutation(sbox_result, perm_result, p4, 4);
    xor_operation(perm_result, r, result, 4);
}
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

// Perform counter mode encryption
void ctr_encrypt(char *plaintext, char *key, char *iv, char *ciphertext) {
    int ctr[8], key_array[10], iv_array[8], temp[8];
    binary_to_array(iv, iv_array, 8);

    for (int i = 0; i < strlen(plaintext); i += 8) {
        // Generate counter value
        array_to_binary(ctr, ciphertext + i, 8);
        // Encrypt counter value
        encrypt_block(ctr, key_array, temp);
        // XOR with plaintext block
        for (int j = 0; j < 8; j++) {
            temp[j] ^= plaintext[i + j] - '0';
        }
        // Convert result to binary string
        array_to_binary(temp, ciphertext + i, 8);
        // Increment counter
        int carry = 1;
        for (int j = 7; j >= 0; j--) {
            ctr[j] += carry;
            carry = (ctr[j] > 1) ? 1 : 0;
            ctr[j] %= 2;
        }
    }
}
void ctr_decrypt(char *ciphertext, char *key, char *iv, char *plaintext) {
    ctr_encrypt(ciphertext, key, iv, plaintext);
}

int main() {
    char plaintext[] = "000000010000001000000100";
    char key[] = "0111111101";
    char iv[] = "00000000";
    char ciphertext[100];

    // Encrypt
    ctr_encrypt(plaintext, key, iv, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt
    char decrypted[100];
    ctr_decrypt(ciphertext, key, iv, decrypted);
    printf("Decrypted plaintext: %s\n", decrypted);

    return 0;
}
