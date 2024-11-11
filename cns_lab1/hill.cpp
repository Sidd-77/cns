#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> multiplyMatrix(vector<vector<int>>& key, vector<int>& text) {
    vector<int> result(text.size(), 0);

    for (int i = 0; i < key.size(); i++) {
        for (int j = 0; j < text.size(); j++) {
            result[i] += key[i][j] * text[j];
        }
        result[i] %= 26;
    }

    return result;
}

string hillEncrypt(string text, vector<vector<int>> key) {
    vector<int> textVec;
    for (char c : text) {
        textVec.push_back(c - 'A');
    }

    vector<int> encryptedVec = multiplyMatrix(key, textVec);
    string encryptedText = "";

    for (int val : encryptedVec) {
        encryptedText += (val + 'A');
    }

    return encryptedText;
}

int main() {
    string text = "ACT";
    vector<vector<int>> key = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    string encrypted = hillEncrypt(text, key);
    cout << "Hill Cipher:\n";
    cout << "Original: " << text << "\n";
    cout << "Encrypted: " << encrypted << "\n";

    return 0;
}
