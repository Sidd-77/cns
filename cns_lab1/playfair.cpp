#include <iostream>
#include <vector>
using namespace std;

string prepareText(const string& text) {
    string prepared;
    for (char c : text) {
        if (c == 'J') {
            prepared += 'I';
        } else {
            prepared += toupper(c);
        }
    }
    return prepared;
}

vector<vector<char>> generateKeyMatrix(const string& key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    string usedChars = "";

    int index = 0;
    for (char c : key) {
        if (usedChars.find(c) == string::npos) {
            usedChars += c;
            matrix[index / 5][index % 5] = c;
            index++;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (usedChars.find(c) == string::npos && c != 'J') {
            matrix[index / 5][index % 5] = c;
            index++;
        }
    }

    return matrix;
}

pair<int, int> findPosition(const vector<vector<char>>& matrix, char c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1};
}

string playfairEncrypt(const string& text, const string& key) {
    vector<vector<char>> matrix = generateKeyMatrix(prepareText(key));
    string preparedText = prepareText(text);

    string encryptedText = "";

    for (size_t i = 0; i < preparedText.length(); i += 2) {
        if (i + 1 == preparedText.length() || preparedText[i] == preparedText[i + 1]) {
            preparedText.insert(i + 1, 1, 'X');
        }

        auto pos1 = findPosition(matrix, preparedText[i]);
        auto pos2 = findPosition(matrix, preparedText[i + 1]);

        if (pos1.first == pos2.first) {
            encryptedText += matrix[pos1.first][(pos1.second + 1) % 5];
            encryptedText += matrix[pos2.first][(pos2.second + 1) % 5];
        } else if (pos1.second == pos2.second) {
            encryptedText += matrix[(pos1.first + 1) % 5][pos1.second];
            encryptedText += matrix[(pos2.first + 1) % 5][pos2.second];
        } else {
            encryptedText += matrix[pos1.first][pos2.second];
            encryptedText += matrix[pos2.first][pos1.second];
        }
    }

    return encryptedText;
}

string playfairDecrypt(const string& text, const string& key) {
    vector<vector<char>> matrix = generateKeyMatrix(prepareText(key));
    string decryptedText = "";

    for (size_t i = 0; i < text.length(); i += 2) {
        auto pos1 = findPosition(matrix, text[i]);
        auto pos2 = findPosition(matrix, text[i + 1]);

        if (pos1.first == pos2.first) {
            decryptedText += matrix[pos1.first][(pos1.second + 4) % 5];
            decryptedText += matrix[pos2.first][(pos2.second + 4) % 5];
        } else if (pos1.second == pos2.second) {
            decryptedText += matrix[(pos1.first + 4) % 5][pos1.second];
            decryptedText += matrix[(pos2.first + 4) % 5][pos2.second];
        } else {
            decryptedText += matrix[pos1.first][pos2.second];
            decryptedText += matrix[pos2.first][pos1.second];
        }
    }

    return decryptedText;
}

int main() {
    string text;
    cout<<"Enter test to encrypt: "<<endl;
    cin>>text;
    string key = "MONARCHY";

    string encrypted = playfairEncrypt(text, key);
    string decrypted = playfairDecrypt(encrypted, key);

    cout << "Playfair Cipher:\n";
    cout << "Original: " << text << "\n";
    cout << "Encrypted: " << encrypted << "\n";
    cout << "Decrypted: " << decrypted << "\n";

    return 0;
}
