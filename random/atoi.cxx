#include<iostream>
using namespace std;

int my_atoi(const char* str) {

  int rValue = 0;
  int isNeg = 1;

  while(*str==' ') { str++;}

  if(*str == '-') {  isNeg = -1; str++;}

  while(str != '\0' && *str >= '0' && *str<='9') {
    rValue = rValue*10 + ( *str - '0');
    str++;
  }
  return rValue * isNeg;

}

int main() {

  cout<<my_atoi("     234");

}
