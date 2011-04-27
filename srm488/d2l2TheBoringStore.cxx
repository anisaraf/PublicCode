#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


void print ( const pair<string, string> &p)
{
   cout<< p.first << ',' << p.second<<endl;
}


class TheBoringStoreDivTwo {
  bool isBetter(const string& prev, const string& curr) const;
public:
  string find(string J, string B); 
};

bool TheBoringStoreDivTwo::isBetter(const string& prev, const string& curr) const {
  return (prev.length() < curr.length() || 
	  (prev.length() == curr.length() && curr.compare(prev) < 0));
}

string TheBoringStoreDivTwo::find(string sj, string sb) {
  
  //generate all pairs from string J and string B
  vector< pair<string, string> > jpairs;
  vector< pair<string, string> > bpairs;
  vector< string > results;
  int ijlen = sj.length();
  int iblen = sb.length();

  for(int i = 0; i < ijlen ; ++i)
    for(int j = i; j < ijlen; ++j)
      for(int k = j+1; k < ijlen; ++k)
	for(int l = k; l < ijlen; ++l)
	  {
	    string a = sj.substr(i,j-i+1);
	    string b = sj.substr(k,l-k+1);
	    if (a.length() > b.length()) {
	      swap(a,b);
	    }

	    if(std::equal(a.begin(), a.end(), b.begin())) {
	      jpairs.push_back( make_pair(a,b.substr(a.length())));
	    }	      
	  }

  for(int i = 0; i < iblen ; ++i)
    for(int j = i; j < iblen; ++j)
      for(int k =j+1; k < iblen; ++k)
	for(int l = k; l < iblen; ++l)
	  {
	    string a = sb.substr(i,j-i+1);
	    string b = sb.substr(k,l-k+1);
	    if (a.length() > b.length()) {
	         swap(a,b);
	    }
	    
	    if(std::equal(a.rbegin(), a.rend(), b.rbegin())) {
	      bpairs.push_back( make_pair(a, b.substr(0,b.length() - a.length())));
	    }	      
	  }

  string result;
  for (int i = 0; i < jpairs.size(); ++i)
      for (int j = 0; j < bpairs.size(); ++j)
	  if(bpairs[j].second == jpairs[i].second) {
	    string curr = jpairs[i].first + bpairs[j].second + bpairs[j].first;
	    result = isBetter(result, curr) ? curr : result;
	  }

  return  result;
}

int main() {
  cout<<"Testing";
  TheBoringStoreDivTwo testobj;
  cout<<"Ans:"<<testobj.find("JohnPlaysGames","BrusAlsoPlays");
}






