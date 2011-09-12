#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

string trim(string s) {
  
  int start; int end; 
  for(start = 0; start < s.length(); start++) {
    if(s[start] != ' ') 
      break;
  }

  for(end = s.length() - 1 ; end > 0; end--) {
    if(s[end] != ' ') 
      break;
  }

  if(start > end) return "";
  string rString(s.begin() + start, s.begin() + end + 1);
  return rString;
}


int main(int argc, char* argv[]){
  string s(argv[1]);
  cout<<"input:"<<s<<"|Output:"<<trim(s)<<"|"<<endl;
}



