#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define KEY_SIZE 100
#define ALPHABET_SIZE 26

char key_square[5][5];

void create_key_square(char key[]) {
  int i, j, len = strlen(key), k = 0;
  char alphabet[ALPHABET_SIZE] = {'\0'};

  // Remove duplicates from the key
  for (i = 0; i < len; i++) {
    if (toupper(key[i]) != 'J' && !strchr(alphabet, toupper(key[i]))) {
      alphabet[k++] = toupper(key[i]);
    }
  }

  // Fill the remaining alphabets (excluding J)
  for (i = 0; i < ALPHABET_SIZE; i++) {
    if (!strchr(alphabet, 'A' + i) && 'A' + i != 'J') {
      alphabet[k++] = 'A' + i;
    }
  }

  // Create the key square
  k = 0;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      key_square[i][j] = alphabet[k++];
    }
  }
}

int get_key_index(char ch) {
  int i, j;
  for (i = 0; i < 5; i++) {
    for (j = 0; j < 5; j++) {
      if (key_square[i][j] == toupper(ch)) {
        return i * 5 + j;
      }
    }
  }
  return -1;
}

void encrypt(char message[]) {
  int i, len = strlen(message);
  for (i = 0; i < len; i += 2) {
    char a, b;
    a = toupper(message[i]);
    b = (i + 1 < len) ? toupper(message[i + 1]) : 'X';

    // Handle double letters
    if (a == b) {
      b = 'X';
      message[i + 1] = b;
    }

    int a_index = get_key_index(a);
    int b_index = get_key_index(b);

    // Same row
    if (a_index / 5 == b_index / 5) {
      message[i] = key_square[a_index / 5][(a_index % 5 + 1) % 5];
      message[i + 1] = key_square[b_index / 5][(b_index % 5 + 1) % 5];
    } else if (a_index % 5 == b_index % 5) {
      // Same column
      message[i] = key_square[(a_index + 5) % 5][a_index % 5];
      message[i + 1] = key_square[(b_index + 5) % 5][b_index % 5];
    } else {
      // Different row and column
      message[i] = key_square[a_index / 5][b_index % 5];
      message[i + 1] = key_square[b_index / 5][a_index % 5];
    }
  }
}

int main() {
  char key[KEY_SIZE], message[KEY_SIZE];

  printf("Enter the key: ");
  fgets(key, KEY_SIZE, stdin);
  key[strcspn(key, "\n")] = '\0'; // Remove newline from key

  printf("Enter the message: ");
  fgets(message, KEY_SIZE, stdin);
  message[strcspn(message, "\n")] = '\0'; // Remove newline from message

  create_key_square(key);
  encrypt(message);

  printf("Encrypted message: %s\n", message);

  return 0;
}
