#include <iostream>
using namespace std;
// Extended Euclidean Algorithm
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


int main() {
    int a ;
    int b ;
    cout << "Enter two numbers: ";
    cin >> a >> b;
    int x, y;
    int gcdResult = extendedGCD(a, b, x, y);
    cout << "Extended GCD of " << a << " and " << b << " is: " << gcdResult << "\n";
    cout << "Coefficients x and y are: " << x << " and " << y << "\n";

    return 0;
}

