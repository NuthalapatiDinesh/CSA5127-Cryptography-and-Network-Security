#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Structure to store letter frequencies
typedef struct {
    char letter;
    int count;
} LetterFrequency;

// Function to calculate letter frequencies in a given string
void calculate_frequencies(const char *text, LetterFrequency *frequencies) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = tolower(text[i]);
            frequencies[letter - 'a'].count++;
        }
    }
}

// Function to compare letter frequencies for sorting
int compare_frequencies(const void *a, const void *b) {
    const LetterFrequency *freq1 = (const LetterFrequency *)a;
    const LetterFrequency *freq2 = (const LetterFrequency *)b;
    return freq2->count - freq1->count; // Sort in descending order of frequency
}

// Function to perform a letter frequency attack on an additive cipher
void letter_frequency_attack(const char *ciphertext, int top_plaintexts) {
    LetterFrequency frequencies[ALPHABET_SIZE] = {0};

    // Calculate letter frequencies in the ciphertext
    calculate_frequencies(ciphertext, frequencies);

    // Find the most frequent letter in the ciphertext (which is likely to be 'e' in English)
    int most_frequent_index = 0;
    for (int i = 1; i < ALPHABET_SIZE; i++) {
        if (frequencies[i].count > frequencies[most_frequent_index].count) {
            most_frequent_index = i;
        }
    }

    // Calculate the additive key based on the frequency of the most frequent letter
    int key = (most_frequent_index - ('e' - 'a') + ALPHABET_SIZE) % ALPHABET_SIZE;

    // Display the top plaintexts based on frequency analysis
    printf("Top %d possible plaintexts:\n", top_plaintexts);
    for (int i = 0; i < top_plaintexts; i++) {
        printf("Key %d: ", key);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            char plaintext_char;
            if (isalpha(ciphertext[j])) {
                if (isupper(ciphertext[j])) {
                    plaintext_char = ((ciphertext[j] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
                } else {
                    plaintext_char = ((ciphertext[j] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
                }
            } else {
                plaintext_char = ciphertext[j];
            }
            printf("%c", plaintext_char);
        }
        printf("\n");
        // Update the key for the next iteration
        key = (key + 1) % ALPHABET_SIZE;
    }
}

int main() {
    const char *ciphertext = "Lxwxq, Jxwrx!";
    int top_plaintexts = 5; // Specify the number of top plaintexts to display

    letter_frequency_attack(ciphertext, top_plaintexts);

    return 0;
}

