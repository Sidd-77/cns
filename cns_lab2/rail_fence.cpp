#include <iostream>
#include <string>
using namespace std;

string railFenceEncrypt(string text, int key) {
    string result;

    // Create an array of strings to store the rails
    string* rail = new string[key];

    // Fill the rail array in a zigzag pattern
    int direction = -1;
    int row = 0;
    for (char c : text) {
        rail[row].push_back(c);
        if (row == 0 || row == key - 1) {
            direction *= -1;
        }
        row += direction;
    }

    // Read the rail array row by row
    for (int i = 0; i < key; i++) {
        result += rail[i];
    }

    delete[] rail;
    return result;
}

string railFenceDecrypt(string cipher, int key) {
    string* rail = new string[key];
    int* len = new int[key]{0};

    int direction = -1;
    int row = 0;
    for (char c : cipher) {
        len[row]++;
        if (row == 0 || row == key - 1) {
            direction *= -1;
        }
        row += direction;
    }

    int index = 0;
    for (int i = 0; i < key; i++) {
        rail[i] = cipher.substr(index, len[i]);
        index += len[i];
    }

    string result;
    direction = -1;
    row = 0;
    int* pos = new int[key]{0};
    for (int i = 0; i < cipher.length(); i++) {
        result.push_back(rail[row][pos[row]]);
        pos[row]++;
        if (row == 0 || row == key - 1) {
            direction *= -1;
        }
        row += direction;
    }

    delete[] rail;
    delete[] len;
    delete[] pos;
    return result;
}

int main() {
    string text;
    cout<<"Enter the text to encrypt: "<<endl;
    cin>>text;
    int key;
    cout<<"Enter key: "<<endl;
    cin>>key;

    string encrypted = railFenceEncrypt(text, key);
    string decrypted = railFenceDecrypt(encrypted, key);

    cout << "Rail Fence Cipher:\n";
    cout << "Original: " << text << "\n";
    cout << "Encrypted: " << encrypted << "\n";
    cout << "Decrypted: " << decrypted << "\n";

    return 0;
}
