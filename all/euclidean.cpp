#include <iostream>
using namespace std;

int gcd(int a, int b){
  while(b != 0){
    int temp = b;
    b = a%b;
    a = temp;
  }
  return a;
}

int main (int argc, char *argv[]) {
  int a, b;
  a = 32;
  b = 12;

  cout<<"GCD of "<<a<<", "<<b<<" is :: "<<gcd(a, b)<<endl;

  return 0;
}
