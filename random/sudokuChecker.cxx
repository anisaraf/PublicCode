#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

const int R = 9;
const int C = 9;

bool checkSudoku(int a[R][C]) {

  // check row
  for(int i = 0; i < C; ++i){
    int resultR = 0;
    int resultC = 0;
    for (int j = 0; j < R; ++j){
      int flagC = 1 << a[i][j];  // set bit(0-8) for value in grid
      int flagR = 1 << a[j][i];
      

      if((resultR & flagR) || (resultC & flagC)){
	cout<<"err"<<resultC<<resultR;
	return false;
      }
      else {
	resultR |=flagR;
	resultC |=flagC;
      }
    }
  }

  // check squares
  int resultS = 0;
  for(int i = 0; i  < 3; i++){
    for (int j = 0; j < 3; ++j){
      // each square
      int resultS = 0;
      for(int sr = 0; sr < 3; sr++){
	for(int sc=0; sc < 3; sc++){
	  int flagS = 1 << a[sr + i*3 ][sc + j*3];
	  if(resultS & flagS)
	    return false;
	  else
	    resultS |=flagS;
	}
      }
    }
  }

  return true;
}





int main(int argc, char *argv[]){
  int a[R][C] = { {4,8,3,9,2,1,6,5,7},
		{2,5,1,8,7,6,4,9,3},
		{5,4,8,1,3,2,9,7,6},
		{7,2,9,5,6,4,1,3,8},
		{1,3,6,7,9,8,2,4,5},
		{3,7,2,6,8,9,5,1,4},
		{8,1,4,2,5,3,7,6,9},
		{9,6,7,3,4,5,8,2,1},
		{6,9,5,4,1,7,3,8,2} };

  cout<<checkSudoku(a);

  return 0;
}
