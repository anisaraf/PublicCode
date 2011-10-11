#include <iostream>
using namespace std;

class TheBoredomDivTwo { 
public:
  int find(int n, int m, int j, int b);
};


int TheBoredomDivTwo::find(int n, int m,int j, int b){
  return n + (j > n ) + (b > n) ;
}

int main () {

  TheBoredomDivTwo c;
  cout<<c.find(4,7,7,4);
  return 1;

}



