#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;


void moveElements(int a[], int size, int element) {
  int skipCount = 0;
  for(int i = size - 1; i >= skipCount; i--) {
    if( a[i] == element){
      skipCount++;
    }
    else 
      a[i+skipCount] = a[i];
  }
  for (int i = 0; i < skipCount; ++i){
    a[i] = element;
  }
}


int main(int argc, char *argv[]){
  
  int a[] = {1,2,4,3,2,1,0,2,5,0,7};
  
  moveElements(a,11,0);
  for (int i = 0; i < 11; ++i){
    cout<<a[i]<<" ";
  }
  
  return 0;
}
