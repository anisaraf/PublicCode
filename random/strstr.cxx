#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;


char* StrStr(char *str, char *target){
  if(!*target) return str;

  char* p1 = str;
  
  while(*p1) {
    char* p1begin = p1; char* p2 = target;
    while(*p1 && *p2 && *p1 == *p2){
      p1++;
      p2++;
    }

    if(!*p2){
      return p1begin;
    } else {
      p1 = p1begin + 1;
    }
  }

  return NULL;
}





int main(int argc, char *argv[]){

  cout<<*StrStr(argv[1],argv[2])<<endl;
  return 0;
}
