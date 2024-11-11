#include <iostream>
#include <string>
using namespace std;

string caesarEncrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += (c - base + shift) % 26 + base;
        } else {
            result += c;
        }
    }

    return result;
}

string caesarDecrypt(string text, int shift) {
    return caesarEncrypt(text, 26 - shift);
}

int main() {
    cout<<"Enter the text to encrypt: "<<endl;
    string text;
    cin>>text;
    int shift = 3;

    string encrypted = caesarEncrypt(text, shift);
    string decrypted = caesarDecrypt(encrypted, shift);

    cout << "Caesar Cipher:\n";
    cout << "Original: " << text << "\n";
    cout << "Encrypted: " << encrypted << "\n";
    cout << "Decrypted: " << decrypted << "\n";

    return 0;
}
