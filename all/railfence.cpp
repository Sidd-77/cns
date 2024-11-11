#include<iostream>
#include<vector>
using namespace std;

string encrypt(string text, int key){
  vector<string> rails(key);
  bool down = true;
  int row = 0;
  for(int i=0; i<text.size(); i++){
    rails[row] += text[i];
    if(down){
      row++;
      if(row==key){
        down = false;
        row--;
        row--;
      }
    }else{
      row--;
      if(row==-1){
        down = true;
        row++;
        row++;
      }
    }
  }

  string encrypted = "";
  for(string s : rails){
    encrypted += s;
  }

  return encrypted;
}

string decrypt(string text, int key){
  vector<string> rails(key);
  bool down = true;
  int row = 0;
  vector<int> railLen(key, 0);
  for(int i=0; i<text.size(); i++){
    railLen[row]++;
    if(down){
      row++;
      if(row==key){
        down = false;
        row--;
        row--;
      }
    }else{
      row--;
      if(row==-1){
        down = true;
        row++;
        row++;
      }
    }
  }
  int tillN = 0;
  for(int i=0; i<key; i++){
    rails[i] = text.substr(tillN, railLen[i]);
    tillN += railLen[i];
  }
  
  string decrypted = "";
  
  vector<int> ind(key,0);
  row = 0;
  for(int i=0; i<text.size(); i++){
    decrypted += rails[row][ind[row]];
    ind[row]++;
    if(down){
      row++;
      if(row==key){
        down = false;
        row--;
        row--;
      }
    }else{
      row--;
      if(row==-1){
        down = true;
        row++;
        row++;
      }
    }
  }
  
  return decrypted;
}

int main (int argc, char *argv[]) {
  int key = 2;
  string text = "HELLOWORLD";
  string encrypted = encrypt(text, key);
  cout<<encrypted<<endl;
  string decrypted = decrypt(encrypted, key);
  cout<<decrypted<<endl;
  return 0;
}
