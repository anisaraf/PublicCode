#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

#define R 3
#define C 6

void spiralPrint(int a[R][C], int m, int n) {

  int sr=0, er=m, sc=0,ec=n;

  while(sr < er && sc < ec) {

    // print first row
    for (int i = sc; i < ec; ++i){
      cout<<a[sr][i]<<" ";
    }
    sr++;

    // print last column
    for (int i = sr; i < er; ++i){
      cout<<a[i][ec-1]<<" ";
    }
    ec--;

    if(sr < er) {
      // print last row
      for (int i = ec-1; i >= sc; --i){
	cout<<a[er-1][i]<<" ";
      }
      er--;

      // print first col
      for (int i = er-1; i >= sr; --i){
	cout<<a[i][sc]<<" ";
      }
      sc++;
    }
  }
  

}

int main(int argc, char *argv[]){
  int a[R][C] = { {1,  2,  3,  4,  5,  6},
		  {7,  8,  9,  10, 11, 12},
		  {13, 14, 15, 16, 17, 18}
  };
 
  spiralPrint(a, R, C);
  return 0; 
}
