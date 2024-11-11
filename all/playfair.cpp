#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

char matrix[5][5];

// Function to create the Playfair matrix using a keyword
void createMatrix(string key) {
    unordered_set<char> used; // To track used characters
    int row = 0, col = 0;

    // Fill matrix with the keyword (excluding duplicate letters and J)
    for (char c : key) {
        if (c == 'J') c = 'I'; // Treat 'I' and 'J' as the same
        if (used.find(c) == used.end()) {
            matrix[row][col++] = c;
            used.insert(c);
            if (col == 5) { col = 0; row++; }
        }
    }

    // Fill remaining spaces in the matrix with other letters
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (used.find(c) == used.end()) {
            matrix[row][col++] = c;
            used.insert(c);
            if (col == 5) { col = 0; row++; }
        }
    }
}

// Function to find the position of a letter in the matrix
pair<int, int> findPosition(char c) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == c)
                return {i, j};
    return {-1, -1}; // This shouldn't happen
}

// Function to prepare the text for encryption (add 'X' if needed)
string prepareText(string text) {
    string result = "";
    for (int i = 0; i < text.length(); i += 2) {
        result += text[i];
        if (i + 1 < text.length()) {
            if (text[i] == text[i + 1])
                result += 'X';  // Insert 'X' between duplicates
            result += text[i + 1];
        }
    }
    if (result.length() % 2 != 0)
        result += 'X'; // Append 'X' if odd length
    return result;
}

// Function to encrypt text using the Playfair cipher rules
string encrypt(string text) {
    text = prepareText(text);
    string encrypted = "";

    for (int i = 0; i < text.length(); i += 2) {
        char a = text[i], b = text[i + 1];
        pair<int, int> posA = findPosition(a);
        pair<int, int> posB = findPosition(b);

        // Same row
        if (posA.first == posB.first) {
            encrypted += matrix[posA.first][(posA.second + 1) % 5];
            encrypted += matrix[posB.first][(posB.second + 1) % 5];
        }
        // Same column
        else if (posA.second == posB.second) {
            encrypted += matrix[(posA.first + 1) % 5][posA.second];
            encrypted += matrix[(posB.first + 1) % 5][posB.second];
        }
        // Rectangle case
        else {
            encrypted += matrix[posA.first][posB.second];
            encrypted += matrix[posB.first][posA.second];
        }
    }
    return encrypted;
}

// Function to decrypt text using the Playfair cipher rules
string decrypt(string text) {
    string decrypted = "";

    for (int i = 0; i < text.length(); i += 2) {
        char a = text[i], b = text[i + 1];
        pair<int, int> posA = findPosition(a);
        pair<int, int> posB = findPosition(b);

        // Same row
        if (posA.first == posB.first) {
            decrypted += matrix[posA.first][(posA.second + 4) % 5];
            decrypted += matrix[posB.first][(posB.second + 4) % 5];
        }
        // Same column
        else if (posA.second == posB.second) {
            decrypted += matrix[(posA.first + 4) % 5][posA.second];
            decrypted += matrix[(posB.first + 4) % 5][posB.second];
        }
        // Rectangle case
        else {
            decrypted += matrix[posA.first][posB.second];
            decrypted += matrix[posB.first][posA.second];
        }
    }
    return decrypted;
}

int main() {
    string key, text;
    cout << "Enter keyword (uppercase letters): ";
    cin >> key;
    cout << "Enter plaintext (uppercase letters): ";
    cin >> text;

    createMatrix(key);

    string encryptedText = encrypt(text);
    cout << "Encrypted text: " << encryptedText << endl;

    string decryptedText = decrypt(encryptedText);
    cout << "Decrypted text: " << decryptedText << endl;

    return 0;
}
