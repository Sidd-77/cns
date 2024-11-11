#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

// Function to multiply two matrices mod 26
vector<int> multiplyMatrix(const vector<vector<int>>& key, const vector<int>& text) {
    int size = key.size();
    vector<int> result(size, 0);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i] += key[i][j] * text[j];
        }
        result[i] %= 26;
    }

    return result;
}

// Function to calculate the modular inverse of a number mod 26
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    throw runtime_error("Inverse doesn't exist");
}

// Function to find the inverse of the key matrix
vector<vector<int>> inverseMatrix(const vector<vector<int>>& key) {
    int n = key.size();
    vector<vector<int>> inverse(n, vector<int>(n));
    int det = 0;

    // Calculate the determinant
    for (int i = 0; i < n; i++) {
        det += key[0][i] * (key[1][(i + 1) % n] * key[2][(i + 2) % n] -
                            key[1][(i + 2) % n] * key[2][(i + 1) % n]);
    }
    det = (det % 26 + 26) % 26;  // Ensure positive mod 26

    if (det == 0) {
        throw runtime_error("Matrix is not invertible");
    }

    // Calculate the inverse using the adjugate method
    int detInverse = modInverse(det, 26);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            // Calculate the cofactor
            int cofactor = ((key[(i + 1) % n][(j + 1) % n] * key[(i + 2) % n][(j + 2) % n]) -
                             (key[(i + 1) % n][(j + 2) % n] * key[(i + 2) % n][(j + 1) % n])) % 26;
            cofactor = (cofactor % 26 + 26) % 26; // Ensure positive mod 26
            inverse[j][i] = (detInverse * cofactor) % 26; // Adjugate and multiply by detInverse
        }
    }

    return inverse;
}

// Function to encrypt plaintext using the Hill Cipher
string hillEncrypt(const string& text, const vector<vector<int>>& key) {
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

// Function to decrypt ciphertext using the Hill Cipher
string hillDecrypt(const string& ciphertext, const vector<vector<int>>& key) {
    vector<int> cipherVec;
    for (char c : ciphertext) {
        cipherVec.push_back(c - 'A');
    }

    vector<vector<int>> invKey = inverseMatrix(key);
    vector<int> decryptedVec = multiplyMatrix(invKey, cipherVec);
    string decryptedText = "";

    for (int val : decryptedVec) {
        decryptedText += (val + 'A');
    }

    return decryptedText;
}

int main() {
    string text = "KAT";
    vector<vector<int>> key = {
        {6, 24, 1},
        {13, 16, 10},
        {20, 17, 15}
    };

    

    // Encrypting
    string encrypted = hillEncrypt(text, key);
    cout << "Hill Cipher:\n";
    cout << "Original: " << text << "\n";
    cout << "Encrypted: " << encrypted << "\n";

    // Decrypting
    string decrypted = hillDecrypt(encrypted, key);
    cout << "Decrypted: " << decrypted << "\n";

    return 0;
}

