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
  if(s.length() == 1) 
    perms.push_back(s);

  for(int i = 0; i < s.length(); i++) {
    string t = s;
    t.erase(i,1);
    vector<string> permsTemp = gen_perm(t);
    for(int j = 0 ; j < permsTemp.size(); j++) {
      permsTemp[j].insert(permsTemp[j].begin(), s[i]);
      perms.push_back(permsTemp[j]);
    }
  }
  return perms;
};



int main(int args, char* argv[]) {

  string s(argv[1]);
  vector<string> p;
  p = gen_perm(s);
  copy ( p.begin(), p.end(), ostream_iterator<string>(cout,"\n") );
  cout<<"Total Perms"<<p.size()<<endl;

}
