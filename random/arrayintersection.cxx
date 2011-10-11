#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;


void arrayIntersection(int a[], int asize, int b[], int bsize) {
  
  sort(a, a + asize);
  sort(b, b + bsize);

  int ia[max(asize,bsize)];
  int ap = 0, bp=0, ip=0;

  while(ap < asize && bp < bsize){
    if(a[ap] == b[bp]){
      ia[ip++] = a[ap++];
    }
    a[ap] < b[bp] ? ap++ : bp++;
  }

  for(int i = 0; i < ip; i++){
    cout<<ia[i]<<" ";
    }
}





int main(int argc, char *argv[]){
  
  int a[] = {3,4,5,6,9,7,3};
  int b[] = {6,4,4,2,3,1,4};

  arrayIntersection(a,7,b,7);
  return 0;
}
