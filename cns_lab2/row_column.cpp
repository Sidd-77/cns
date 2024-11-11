#include <iostream>
#include <string>
#include <vector>
using namespace std;


string columnarEncrypt(string text, string key) {
    int numRows = (text.length() + key.length() - 1) / key.length();
    vector<string> grid(numRows, string(key.length(), ' '));

    int index = 0;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key.length(); j++) {
            if (index < text.length()) {
                grid[i][j] = text[index++];
            }
        }
    }

    string encryptedText;
    for (char c : key) {
        int col = c - '1'; // Assuming the key is a permutation of "123..."
        for (int i = 0; i < numRows; i++) {
            encryptedText += grid[i][col];
        }
    }

    return encryptedText;
}

string columnarDecrypt(string cipher, string key) {
    int numRows = (cipher.length() + key.length() - 1) / key.length();
    vector<string> grid(numRows, string(key.length(), ' '));

    int index = 0;
    for (char c : key) {
        int col = c - '1';
        for (int i = 0; i < numRows; i++) {
            if (index < cipher.length()) {
                grid[i][col] = cipher[index++];
            }
        }
    }

    string decryptedText;
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < key.length(); j++) {
            decryptedText += grid[i][j];
        }
    }

    return decryptedText;
}

int main() {
    string text;
    cout<<"Enter the text to encrypt: "<<endl;
    cin>>text;
    string key = "3124";

    string encrypted = columnarEncrypt(text, key);
    string decrypted = columnarDecrypt(encrypted, key);

    cout << "Columnar Transposition Cipher:\n";
    cout << "Original: " << text << "\n";
    cout << "Encrypted: " << encrypted << "\n";
    cout << "Decrypted: " << decrypted << "\n";

    return 0;
}
