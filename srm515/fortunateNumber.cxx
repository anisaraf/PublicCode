#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>
#include <map>
#include <set>

using namespace std;


class FortunateNumbers {

  bool isFortunate(int n) {
    while(n  > 0) {
      int digit = n % 10;
      if(digit != 5 && digit != 8)
	return false;
      n /=10;
    }
    return true;
  }

public:
  int getFortunate(vector<int> a, vector<int> b, vector<int> c){
    set<int> fortunates;

    for(int i= 0; i < a.size(); ++i)
      for(int j = 0; j < b.size(); ++j) 
	for(int k = 0 ; k < c.size(); ++k) {
	  int num = a[i] + b[j] + c[k];
	  if(isFortunate(num)) {
	    fortunates.insert(num);
	  }
	}
    return fortunates.size();
  }
};
  
  
int main(int argc, char *argv[]){
  
  return 0;
}


/* Problem Statement: Lecette thinks that 5 and 8 are fortunate
   digits. A positive integer is called a fortunate number if it has only
   fortunate digits in its decimal representation.  You are given three
   vector <int>s a, b and c. Return that number of fortunate numbers
   which can be expressed as a[i] + b[j] + c[k] for some indices i, j and
   k. Note that you must not count the same fortunate number more than
   once. 


   Constraints
   -
   a, b and c will each contain between 1 and 50 elements, inclusive.
   -
   Each element of a, b and c will be between 1 and 30,000, inclusive.
   Examples
   0)

       
   { 1, 10, 100 }
   { 3, 53 }
   { 4, 54 }
   Returns: 2
   We have two fortunate numbers 8 = 1 + 3 + 4 and 58 = 1 + 3 + 54. 58 can be also expressed as 1 + 53 + 4, but you must not count 58 twice.

*/
