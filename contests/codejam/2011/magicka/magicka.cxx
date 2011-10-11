#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <iterator>
using namespace std;


class Magicka {

private: 

  map<string, char> m_CombineMap;
  map<char,char> m_OpposeMap;

  string m_OpposeListCurrent;
  vector<char> m_currList;

  void addCombineElement(const string& elem){
    string a = elem.substr(0,2);
    sort(a.begin(),a.end());
    m_CombineMap.insert(pair<string, char>(a,elem[2]));
  }

  void addOpposeElement(string str){
    m_OpposeMap.insert(pair<char, char>(str[0],str[1]));
    m_OpposeMap.insert(pair<char, char>(str[1],str[0]));
  }

  void addInvoke(char c) {
    // check combination
    string combine (1,c);
    if(!m_currList.empty()) {
      combine.append(1,m_currList.back());
      sort(combine.begin(), combine.end());
    }
    
    map<string, char>::iterator it = m_CombineMap.find(combine);
    if(it!= m_CombineMap.end()) {
      char removed = m_currList.back();
      m_currList.pop_back();
      c = it->second;

      // remove blowup if combined
      map<char, char>::iterator it = m_OpposeMap.find(removed);
      int length = m_OpposeListCurrent.length();
      if( length > 0 && m_OpposeListCurrent[length -1] == it->second)
	m_OpposeListCurrent[length - 1] = '\0';
    }
    m_currList.push_back(c);

    //  empty list?
    if(m_OpposeListCurrent.find(c) != string::npos) {
      m_currList.clear();
      m_OpposeListCurrent = "";
      }else {
      // add opposing char to blow up list
	map<char, char>::iterator it = m_OpposeMap.find(c);
	if(it != m_OpposeMap.end())
	  m_OpposeListCurrent.append(1,it->second);
    }
  }
    

public: 

  vector<char> start(const string& sCaseData) {
    istringstream in(sCaseData);
    
    int totalCombinations;
    int totalOpposes;
    
    in >> totalCombinations;
    for(int i = 0; i < totalCombinations; ++i){
      string combination;
      in >> combination;
      addCombineElement(combination);
    }


    in >> totalOpposes;
    for(int i = 0; i < totalOpposes; ++i){
      string oppose;
      in >> oppose;;
      addOpposeElement(oppose);
    }
    
    int totalInvokes;
    string sInvokes;
    in >> totalInvokes >> sInvokes;
    for_each(sInvokes.begin(), sInvokes.end(), bind1st(mem_fun(&Magicka::addInvoke), this));
    return m_currList;
  }
};

int main() { 

  int totalCases;
  string caseData;


  cin >> totalCases;
  cin.ignore();
  for (int j = 1; j <= totalCases; j++)
    {
      Magicka m;
      getline(cin, caseData);
      vector<char> v  = m.start(caseData);
    
      printf("Case #%i: [",j);
      if(v.empty()) 
	printf("]\n");
      for(int i = 0; i < v.size(); i++) {
	cout<<v[i];
	if( i < v.size() -1)
	  cout<<", ";
	else
	  cout<<"]\n";
      }
      
    }
  return 1;

}
