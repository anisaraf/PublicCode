#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class MarbleDecoration {
public:
  int maxLength(int R, int G, int B);
};

int MarbleDecoration::maxLength(int R, int G, int B) {
  vector<int> v;
  v.push_back(R);
  v.push_back(G);
  v.push_back(B);
  sort(v.begin(), v.end());

  return v[1] * 2 + (v[1]==v[2] ? 0 : 1);
}
 
int main(){
  MarbleDecoration test;
  test.maxLength(13,13,13);
}
