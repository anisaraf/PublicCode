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
#include <stack>

using namespace std;

bool isOperator(const string& s) {s
  return (s == "+" || s == "-" || s=="*");
}

int postfixCalculator(const vector<string>& elements) {
  stack<int> s;
  
  for (int i = 0; i < elements.size(); ++i){
    if(isOperator(elements[i])) {
      int operandB = s.pop();
      int operandA = s.pop();
   
      if(elements[i] == '+')
	s.push(operandA + operandB);
      if(elements[i] == '-')
	s.push(operandA - operandB);
      if(elements[i] == '*')
	s.push(operandA * operandB);
    } else {
      s.push(atoi(elements[i]));
    }
  }

  if(s.size() != 1) return NULL;
  return s.pop();


}





int main(int argc, char *argv[]){
  
  return 0;
}

