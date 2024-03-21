#include <iostream>
#include <cstring>
using namespace std;

void decrypt(char* ciphertext, char* mapping) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            cout << mapping[ciphertext[i] - 'A'];
        } else {
            cout << ciphertext[i];
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡8†83 (88)5†;46(;88*96*?;8)‡(;485);5†2:‡(;4956*2(5—4)8¶8* ;4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?";
    char mapping[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* freq_mapping = new char[26];
    strcpy(freq_mapping, "ETAONRISHDLFCMUGYPWBVKXJQZ"); 

    cout << "Decrypted Message:" << endl;
    decrypt(ciphertext, freq_mapping);
    cout << endl;

    delete[] freq_mapping;
    return 0;
}
