#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

int maxsubarray(int in[], size_t n, size_t& maxStart, size_t& maxEnd) {
  int max_so_far = 0;
  int max_here = 0; 

  int start =0,  end = 0;
  maxStart = maxEnd = 0;

  for(int i = 0; i < n; i++){
    max_here = max(0, max_here + in[i]);
    if(max_here == 0)
      start = i + 1;

    if(max_so_far < max_here) {
      end = i;
      maxStart = start;
      maxEnd = end;
      max_so_far = max_here;
    } 
  }
  return max_so_far;  
}


int main() {
  int arr[] = {-2, 1, -3, 4, -1, 2, 1, -10, 400};
  size_t start = 0, end =0;;

  cout<<maxsubarray(arr, sizeof(arr)/sizeof(int), start, end) ; 
  cout <<" "<<start<<" "<<end;
  
}
