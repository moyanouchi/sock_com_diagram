#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
using namespace std;

// int * 1 [4 byte] -> char * 4 [4 byte] を行う
string itoa(int num){
  const static int byte = 4;
  char tmp[byte + 1] = {};
  memcpy(tmp, &num, byte);
  // NULL 文字の場合、加算が打ち切られるため
  // 全ての文字をループにより、加算する
  string str;
  for(int i = 0; i < byte; i++){
    str += tmp[i];
  }
  
  return str;
}

//  char * 4 [4 byte] -> int * 1 [4 byte] を行う
int atoi(string str){
  int num;
  memcpy(&num, str.c_str(), sizeof(int));
  return num;
}

int main(int argc, char *argv[]){
  // 送信したい文字列
  string str;
  cout << "メッセージ: ";
  cin >> str;

  // フォーマット用のヘッダ
  int head_id = 0x87654321;
  int send_id = 0;
  int sequence = 0;
  int body_length = str.length();

  // フォーマットに従った送信文
  string msg;
  msg += itoa( head_id);
  msg += itoa(send_id);
  msg += itoa(sequence);
  msg += itoa(body_length);
  msg += str;

  // データが正しく生成できているか、確認する
  cout << "head_id: " << atoi(msg.substr(0, 4)) << endl;
  cout << "send_id: " <<  atoi(msg.substr(4, 4)) << endl;
  cout << "sequenc: " << atoi(msg.substr(8, 4)) << endl;
  cout << "body_length: " << atoi(msg.substr(12, 4)) << endl;
  cout << "メッセージ: " << msg.substr(16) << endl;

  return 0;
}
