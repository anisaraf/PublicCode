#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class MarbleDecoration {
public:
  int maxLength(int R, int G, int B);
};

int MarbleDecoration::maxLength(int R, int G, int B) {
  vector<int> v;
  v.push_back(R);
  v.push_back(G);
  v.push_back(B);
  sort(v.begin(), v.end());

  return v[1] * 2 + (v[1]==v[2] ? 0 : 1);
}
 
int main(){
  MarbleDecoration test;
  test.maxLength(13,13,13);
}


/* Problem Statement A mysterious new restaurant is open in the city
for only N days. Happy to hear that, Ash and Elsh would like to have
lunch at the restaurant on as many days as possible.  The restaurant
sells M types of dishes. Being a mysterious restaurant, it has
mysterious rules for the customers:

They can only buy one single dish per day.  If they buy a dish of type
j on the i-th day, then on the same day next week, i.e., on the
(i+7)-th day, they can only buy a dish of type j.  If they don't buy
any dishes on any day, then they can't buy any dishes again from the
restaurant.


Mysteriously, the price of each type of dish varies every day. You are
given a String[] prices consisting of N elements, each containing M
characters. prices[i][j] represents the price of the j-th type of dish
on the i-th day, encoded as follows:

'0' - '9': denotes the price of 0 - 9 dollars.  'A' - 'Z': denotes the
price of 10 - 35 dollars.  'a' - 'z': denotes the price of 36 - 61
dollars.


Ash and Elsh have only budget dollars allocated for having lunch in
the restaurant. Return the maximum number of days they could have
lunch in the restaurant.  */
