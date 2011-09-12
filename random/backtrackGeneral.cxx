#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

template <typename T>
class Backtrack
{

private:
  bool finished;
  int NMAX;
  int MAXCANDIDATES;
  T data;

public:
  int solutionCount;
  Backtrack(int nmax, int maxCandidates, T extraData) : solutionCount(0), 
							finished(false), 
							NMAX(nmax),
							MAXCANDIDATES(maxCandidates),
							data(extraData){};
  void backtrackStart(int a[], int size);
  bool isSolution(int a[], int size);
  void processSolution(int a[], int size);
  void constructCandidates(int a[], int size, int c[], int& maxCandidates);
};


template <typename T> void Backtrack<T>::backtrackStart(int a[], int size) {
  int c[MAXCANDIDATES]; // candidates for next postion
  int nCandidates; // next position candidate count

  if(isSolution(a, size)) {
    this->solutionCount++;
    processSolution(a, size);
  } else {
    constructCandidates(a, size, c, nCandidates);
    size = size + 1;
    for (int i = 0; i < nCandidates; ++i)  {
	a[size-1] = c[i];
	backtrackStart(a,size);
	if(finished) return;
      }
  }
}

template <typename T> bool Backtrack<T>::isSolution(int a[], int size) {
}

template <typename T> void Backtrack<T>::processSolution(int a[], int size) {
}

template <typename T> void Backtrack<T>::constructCandidates(int a[], int size, int c[], int& nCandidates) {
}


int main(int argc, char *argv[])
{
  
}
