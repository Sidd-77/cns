#include<iostream>
#include <string>
using namespace std;

string ceaser(string text, int shift){
  string output = "";

  for(int i=0; i<text.size(); i++){
    if(isupper(text[i])){
      output += char(int(text[i]+shift - 'A')%26 + 'A');
    } else {
      output += char(int(text[i]+shift - 'a')%26 + 'a');
    }
  }

  return  output;
}

string decrypt(string text, int shift){
  string output = "";

  for(int i=0; i<text.size(); i++){
    if(isupper(text[i])){
      output += char(int(text[i]-shift - 'A')%26 + 'A');
    } else {
      output += char(int(text[i]-shift - 'a')%26 + 'a');
    }
  }

  return  output;

}

int main (int argc, char *argv[]) {
  int shift = 3;
  string input;
  cout<<"Enter the string : ";
  getline(cin, input);

  string output = ceaser(input, shift);

  cout<<"Output is :: "<<output<<endl;

  string decrypted = decrypt(output, shift);

  cout<<"Decrypted test is :: "<<decrypted<<endl;
  return 0;
}
