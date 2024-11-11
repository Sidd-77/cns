#include <iostream>
#include <vector>
using namespace std;
// Function to find the Greatest Common Divisor (GCD)
int gcd(int a, int b) {
    return (b == 0) ? a : gcd(b, a % b);
}

// Extended Euclidean Algorithm to find modular inverse
int extendedGCD(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;

    return gcd;
}

// Function to find modular inverse of a under modulo m
int modInverse(int a, int m) {
    int x, y;
    int gcd = extendedGCD(a, m, x, y);

    // If gcd is 1, then modular inverse exists
    if (gcd != 1) {
        cerr << "Modular inverse doesn't exist\n";
        return -1;
    }

    return (x % m + m) % m;
}

// Function to implement the Chinese Remainder Theorem
int chineseRemainderTheorem(vector<int> num, vector<int> rem) {
    int prod = 1; // Product of all num[i]
    for (int n : num) {
        prod *= n;
    }

    int result = 0;

    // Apply the formula:
    // x = (sum of all (rem[i] * pp[i] * inv[i])) % prod
    for (int i = 0; i < num.size(); i++) {
        int pp = prod / num[i];
        int inv = modInverse(pp, num[i]);
        if (inv == -1) return -1;
        result += rem[i] * pp * inv;
    }

    return result % prod;
}

int main() {
    // Example inputs
    vector<int> num = {3, 4, 5}; // Moduli
    vector<int> rem = {2, 3, 1}; // Remainders

    int x = chineseRemainderTheorem(num, rem);

    if (x != -1) {
        cout << "x is " << x << endl;
    } else {
        cerr << "Solution does not exist" << endl;
    }

    return 0;
}
