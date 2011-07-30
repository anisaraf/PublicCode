#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

class MysteriousRestaurant {
  int getPrice(char p);
  bool isDayValid(vector<string> prices, int budget,int days);
public:
  int  maxDays(vector<string> prices, int budget);
};


int MysteriousRestaurant::getPrice(char p) {
  if( p >='0' && p<='9') 
    return p - '0';
  else if (p >='A' && p<='Z')
    return 10 + (p - 'A');
  else if (p >= 'a' && p <='z')
    return 36 + (p - 'a');
  return -1;
}

bool MysteriousRestaurant::isDayValid(vector<string> prices, int budget,int days) {
  int totalDishes = prices[0].length();
  if( days > prices.size()) 
    return false;

  for(int d = 0 ; d < 7 && d < days ; d++) {
    int mindish = INT_MAX;
    for(int i = 0; i < totalDishes ; i++) {
      int pDay = 0;
      for(int j = d; j < days ; j+=7) {
	if(j < days) pDay +=getPrice(prices[j][i]);
      }
      mindish = pDay < mindish ? pDay : mindish;
    }
    budget -=mindish;
    //printf("day %i budget %i mindish %i  \n", d, budget, mindish);
    if(budget < 0) return false;
  }
  return true;
}

int MysteriousRestaurant::maxDays(vector<string> prices, int budget) {
  int d = 1;
  while(isDayValid(prices, budget, d)) {
    d++;
  }
  return (d-1);
}
 
template<typename T, size_t N>
T * end(T (&ra)[N]) {
  return ra + N;
}

int main(){
  string prices[] = {"26", "14", "72", "39", "32", "85", "06"};
  vector<string> p(prices, end(prices));

  MysteriousRestaurant m;
  cout<<"max days"<<m.maxDays(p, 13)<<endl;

  ostream_iterator<string> out_it (cout,"\n ");
  copy ( p.begin(), p.end(), ostream_iterator<string>(cout,"\n") );

  
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
