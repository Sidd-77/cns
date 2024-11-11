#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<int>> key = {
  {6, 24},
  {1, 13}
};

vector<vector<int>> invKey = {
  {8, 5},
  {17, 15}
};

vector<int> multiplyMat(vector<vector<int>> mat, vector<int> vec){
  vector<int> result(vec.size());
  result[0] = (mat[0][0]*vec[0] + mat[0][1]*vec[1]) % 26;
  result[1] = (mat[1][0]*vec[0] + mat[1][1]*vec[1]) % 26;
  if (result[0] < 0) result[0] += 26;
  if (result[1] < 0) result[1] += 26;
  return result;
}


string encrypt(string text){
  string output = "";
  for(int i=0; i<text.size(); i+=2){
    vector<int> block = {text[i]-'A', text[i+1]-'A'};
    vector<int> result = multiplyMat(key, block);
    output += (result[0]+'A');
    output += (result[1]+'A');
  }

  return output;
}

string decrypt(string text){
  string output = "";
  for(int i=0; i<text.size(); i+=2){
    vector<int> block = {text[i]-'A', text[i+1]-'A'};
    vector<int> result = multiplyMat(invKey, block);
    output += (result[0]+'A');
    output += (result[1]+'A');
  }
  return output;
}

int main (int argc, char *argv[]) {
  string input;
  cout<<"Input Text :: ";
  getline(cin, input);
  string encrypted = encrypt(input);
  cout<<"Encrypted Text :: "<<encrypted<<endl;
  string decrypted = decrypt(encrypted);
  cout<<"Decrypted Text :: "<<decrypted<<endl;
  return 0;
}
