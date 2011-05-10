#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>

using namespace std;


class Robot {
  int m_currPos;
  int m_accumulatedSeconds;

public:
  Robot() : m_currPos(1), m_accumulatedSeconds(0) {} ;
  int moveMe(int position) {
    int requiredSeconds = abs(position - m_currPos) - m_accumulatedSeconds + 1;
    m_accumulatedSeconds = 0;
    m_currPos = position;
    return requiredSeconds > 0 ? requiredSeconds : ;
  }

  int accumulateSeconds(int seconds){
    m_accumulatedSeconds+=seconds;
  }

};

class Game {  

public:
  int move(Robot& rMove, Robot& rAccumulate, int pos)
  {
    int secs = rMove.moveMe(pos);
    rAccumulate.accumulateSeconds(secs);
    return secs;
  }

  int start(const string& moves) { 
    istringstream in(moves);
    int nextPos;
    char nextRobot;
    int totalSeconds=0;
    Robot ro, rb;
    int totalMoves;
    
    in >> totalMoves;
    while(! in.eof()) {
      in>>nextRobot>>nextPos;
      if(nextRobot == 'O') 
	totalSeconds += this->move(ro , rb, nextPos);     
      else
	totalSeconds += this->move(rb , ro, nextPos);
    }
      
    return totalSeconds;
    

  }
  
};

int main() {

  Game g;
  string moves;
  int totalCases;

  cin>>totalCases;
  cin.ignore();
  for (int i = 1; i <= totalCases; ++i)
    {
      getline(cin, moves);
      int totalTime = g.start(moves);
      printf("Case #%i: %i\n",i,totalTime);
    }
  return 1;
}
