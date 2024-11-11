#include <iostream>
using namespace std;

string generateKey(string text, string key){
  int tlen = text.size();
  int klen = key.size();
  string generatedKey = key;
  while(generatedKey.size() < text.size()){
    generatedKey += key;
  }

  return generatedKey.substr(0, tlen);
}


string encrypt(string text, string key){
  string encrypted = "";
  for(int i=0; i<text.size(); i++){
    char enc = (text[i]+key[i]-'a'-'a') % 26 + 'a';
    encrypted += enc;
  }
  return encrypted;
}


string decrypt(string text, string key){
  string encrypted = "";
  for(int i=0; i<text.size(); i++){
    char enc = (text[i]-key[i] + 26) % 26 + 'a';
    encrypted += enc;
  }
  return encrypted;
}

int main (int argc, char *argv[]) {
  string key = "key";
  string text = "hellohello";
  string generatedKey = generateKey(text, key);
  string encrypted = encrypt(text, generatedKey);
  string decrypted = decrypt(encrypted, generatedKey);

  cout<<generatedKey<<endl;
  cout<<encrypted<<endl;
  cout<<decrypted<<endl;
  return 0;
}
