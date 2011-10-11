#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <map>

using namespace std;


int compare(const void* a, const void* b) {
  return (*(int*) a - *(int*) b);

}

int main(int argc, char *argv[]){
  
  map<int, int> m;
  int a[] = { 0,9,19,-9,10,12,15 };

  // method 1
  for (int i = 0; i < sizeof(a)/sizeof(int); ++i){
    if( m.find(-a[i]) != m.end())
      cout<<a[i]<<"=0\n";
    m[a[i]] = 1;
  }

  // method 2
  qsort(a, sizeof(a) / sizeof(int), sizeof(int), compare);
  
  int i =0, j=sizeof(a) / sizeof(int) -1;
  
  while(i < j) {
    if(a[i] + a[j] == 0){
      printf("\n %i + %i = 0", a[i],a[j]);
     j = i;
    } else {
      a[i] + a[j] > 0 ? j-- : i++;
    }
    
  }

  for (int i = 0; i < sizeof(a)/sizeof(int); ++i){
    cout<<endl<<a[i]<<" ";
  }


  
  return 0;
}
