#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

void twoSum(int numbers[], int size, int target, int &index1, int &index2) {
  // Start typing your C/C++ solution below
  // DO NOT write int main() function
  // NO #include's are required

  sort(numbers, numbers + size);
  index1 = 1;
  index2 = size;
  while(index1 < index2) {
    int sum = numbers[index1-1] + numbers[index2 -1];
    if(sum == target)
      return;
    else if(sum < target)
      index1++;
    else
      index2--;
  }
}






int main(int argc, char *argv[]){
  int a[] = {150,24,79,50,88,345,3};
  int b =0;
  int c= 0;
  twoSum(a,7,200,b,c);
  cout<<b<<c;
  return 0;
}



