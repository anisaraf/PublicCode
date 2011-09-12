#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;


class MonochromaticBoard {

  int theMin(vector<string> board) {
    bool allBlacks = true;
    map<int,int> cols;
    int moves = 0;

    for (int i = 0; i < board.size(); ++i){
      size_t wl = board[i].find_first_not_of("B");
      if(wl != string::npos) {
	allBlacks = false;
	// knock of each required column since we can't clean up row
	for(int j = 0 ; j < board[i].length(); ++j) {
	  if(board[i][j] == 'B' && cols.find(j) == cols.end()) {
	    cols[j] = 1;
	    moves++;
	  }
	}
      } else {
	//entire row is black - so one move to knock it all off
	moves++;
      }	
    }
    
    if(allBlacks) 
      // all blacks; get min of row/col count
      return min(board.size(), board[0].length());
    else 
      return moves;
  }
};


int main(int argc, char *argv[]){
  
  return 0;
}


/*
Problem Statement : There is a HxW rectangular board divided into
1x1 cells. Initially each cell is colored White. Fox Ciel wants to
change the color of certain cells on the board. You are given a vector
<string> board consisting of characters 'B' and 'W'. If the j-th
character of the i-th element of board is 'B', she must change the
color of cell (i, j) to Black, otherwise this cell must remain White.
Fox Ciel can perform the following operation: 1. Choose one row or one
column. 2. Paint the row or the column she chose in step 1 with
Black. The color of all cells in the row or the column becomes Black.
Return the minimal number of operations required to change the color
to board. The constraints will guarantee that it's always possible.
Definition
 Class: MonochromaticBoard Method: theMin Parameters:
vector <string> Returns: int Method signature: int theMin(vector
<string> board) (be sure your method is public)

Constraints
-
board will contain between 1 and 50 elements, inclusive.
-
Each element of board will contain the same number of characters.
-
Each element of board will contain between 1 and 50 characters, inclusive.
-
Each character in board will be 'W' or 'B'.
-
board can be obtained by performing the operation described in the statement 0 or more times.

Examples
0)
{"WBWBW",
 "BBBBB",
 "WBWBW",
 "WBWBW"}
 Returns: 3
Paint row 1 (0-indexed), column 1 and column 3.

1)

{"BBBB",
 "BBBB",
 "BBBB"}
 Returns: 3
Paint all rows.

2)

{"BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB",
 "BBBBB"}
 Returns: 5
Paint all columns.

3)
{"WW",
 "WW"}
 Returns: 0

4)
{"BBBBBBBB",
 "BBBBBBBB",
 "BBBBBBBB",
 "WBWBBBWB",
 "BBBBBBBB"}
 Returns: 9


*/
