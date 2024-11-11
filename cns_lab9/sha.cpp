#include <iostream>
#include <iomanip>
#include <openssl/sha.h>
using namespace std;

void computeSHA1(const string &input){
    // Create a buffer to store the hash output (20 bytes for SHA-1)
    unsigned char hash[SHA_DIGEST_LENGTH];

    // Perform the SHA-1 hash operation
    SHA1((unsigned char *)input.c_str(), input.size(), hash);

    // Output the hash in hexadecimal format
    cout << "SHA-1 Hash: ";
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        cout << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    cout << endl;
}

int main(){
    string inputText;
    cout << "Enter text: ";
    getline(cin, inputText);

    // Calculate and display the SHA-1 hash
    computeSHA1(inputText);

    return 0;
}
