#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

vector<string> gen_perm(string s) {

  vector<string> perms;
  for(int i = 0; i < s.length(); i++) {
    char addMe = s[i];
    s.erase(i,1);
    vector<string> permsTemp = gen_perm(s);
    for_each(permsTemp.begin(), permsTemp.end(), [&](string elem) { 
	elem.insert(elem.begin(), addMe);
	perms.push_back(elem);
      });
  }
  return perms;
};



int main() {

  vector<string> p;
  p = gen_perm("test");
  copy ( p.begin(), p.end(), ostream_iterator<string>(cout,"\n") );

}
