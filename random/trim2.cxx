#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;


const string whitespaces(" \f\n\r\t\v");

void ltrim(string& s, const string& trim = whitespaces) {
  size_t pos = s.find_first_not_of(trim);
  s.erase(0,pos);
}

void rtrim(string& s, const string& trim = whitespaces) {
  size_t pos = s.find_last_not_of(trim);
  s.erase(pos+1);

}

void trim(string& s, const string& trim = whitespaces) {
  ltrim(s, trim);
  rtrim(s, trim);
}

int main(int argc, char* argv[]){
  string s(argv[1]);
  cout<<"input:"<<s;
  trim(s);
  cout<<"|Output:"<<s<<"|"<<endl;
}



