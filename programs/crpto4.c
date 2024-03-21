#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define ALPHABET_SIZE 26

char shift_table[ALPHABET_SIZE][ALPHABET_SIZE];

void create_shift_table(char key[]) {
  int i, j, key_len = strlen(key);
  for (i = 0; i < ALPHABET_SIZE; i++) {
    for (j = 0; j < ALPHABET_SIZE; j++) {
      shift_table[i][j] = (char) ((toupper(key[(j % key_len)]) - 'A' + i) % ALPHABET_SIZE + 'A');
    }
  }
}

void encrypt(char message[], char key[]) {
  int i, j, key_len = strlen(key);
  for (i = 0; message[i] != '\0'; i++) {
    if (isalpha(message[i])) {
      int shift = toupper(key[i % key_len]) - 'A';
      message[i] = shift_table[toupper(message[i]) - 'A'][shift];
    }
  }
}

int main() {
  char message[100], key[100];

  printf("Enter the message: ");
  fgets(message, 100, stdin);
  message[strcspn(message, "\n")] = '\0'; // Remove newline from message

  printf("Enter the key: ");
  fgets(key, 100, stdin);
  key[strcspn(key, "\n")] = '\0'; // Remove newline from key

  create_shift_table(key);
  encrypt(message, key);

  printf("Encrypted message: %s\n", message);

  return 0;
}
