#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to generate the column order based on keyword
vector<int> getColumnOrder(string keyword) {
    int len = keyword.length();
    vector<pair<char, int>> keyPositions;
    for (int i = 0; i < len; i++) {
        keyPositions.push_back({keyword[i], i});
    }
    sort(keyPositions.begin(), keyPositions.end()); // Sort by character

    vector<int> order;
    for (auto& p : keyPositions) {
        order.push_back(p.second);
    }
    return order;
}

// Function to encrypt the plaintext using Row-Column cipher
string encrypt(string text, string keyword) {
    int numCols = keyword.length();
    int numRows = (text.length() + numCols - 1) / numCols; // Round up for padding

    // Create a grid with padding if necessary
    vector<vector<char>> grid(numRows, vector<char>(numCols, 'X')); // Fill grid with 'X'
    int index = 0;

    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            if (index < text.length()) {
                grid[row][col] = text[index++];
            }
        }
    }

    // Get the column order based on the keyword
    vector<int> colOrder = getColumnOrder(keyword);

    // Read columns in the specified order to create the encrypted text
    string encryptedText = "";
    for (int col : colOrder) {
        for (int row = 0; row < numRows; row++) {
            encryptedText += grid[row][col];
        }
    }
    return encryptedText;
}

// Function to decrypt the ciphertext using Row-Column cipher
string decrypt(string text, string keyword) {
    int numCols = keyword.length();
    int numRows = (text.length() + numCols - 1) / numCols;

    // Get the column order based on the keyword
    vector<int> colOrder = getColumnOrder(keyword);

    // Create a grid and fill columns by order from the ciphertext
    vector<vector<char>> grid(numRows, vector<char>(numCols));
    int index = 0;

    for (int col : colOrder) {
        for (int row = 0; row < numRows; row++) {
            if (index < text.length()) {
                grid[row][col] = text[index++];
            }
        }
    }

    // Read the grid row by row to reconstruct the original text
    string decryptedText = "";
    for (int row = 0; row < numRows; row++) {
        for (int col = 0; col < numCols; col++) {
            decryptedText += grid[row][col];
        }
    }

    return decryptedText;
}

int main() {
    string text, keyword;
    cout << "Enter plaintext: ";
    cin >> text;
    cout << "Enter keyword: ";
    cin >> keyword;

    string encryptedText = encrypt(text, keyword);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText, keyword);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
