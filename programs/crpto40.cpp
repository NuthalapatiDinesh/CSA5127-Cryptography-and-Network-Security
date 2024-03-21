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

// Function to perform a letter frequency attack on a monoalphabetic substitution cipher
void letter_frequency_attack(const char *ciphertext, int top_plaintexts) {
    LetterFrequency frequencies[ALPHABET_SIZE] = {0};

    // Calculate letter frequencies in the ciphertext
    calculate_frequencies(ciphertext, frequencies);

    // Sort the letter frequencies
    qsort(frequencies, ALPHABET_SIZE, sizeof(LetterFrequency), compare_frequencies);

    // Define the mapping from most frequent ciphertext letters to English letters
    char mapping[ALPHABET_SIZE];
    const char *english_frequencies = "etaoinshrdlcumwfgypbvkjxqz";
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        mapping[frequencies[i].letter - 'a'] = english_frequencies[i];
    }

    // Display the top plaintexts based on frequency analysis
    printf("Top %d possible plaintexts:\n", top_plaintexts);
    for (int i = 0; i < top_plaintexts; i++) {
        printf("Attempt %d: ", i + 1);
        for (int j = 0; ciphertext[j] != '\0'; j++) {
            char plaintext_char;
            if (isalpha(ciphertext[j])) {
                if (isupper(ciphertext[j])) {
                    plaintext_char = toupper(mapping[ciphertext[j] - 'A']);
                } else {
                    plaintext_char = mapping[ciphertext[j] - 'a'];
                }
            } else {
                plaintext_char = ciphertext[j];
            }
            printf("%c", plaintext_char);
        }
        printf("\n");
    }
}

int main() {
    const char *ciphertext = "Lxwxq, Jxwrx!";
    int top_plaintexts = 5; // Specify the number of top plaintexts to display

    letter_frequency_attack(ciphertext, top_plaintexts);

    return 0;
}

