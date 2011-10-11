#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

class DoubleRoshambo {
  int maxScore(vector<string> a, vector<string> b);
};

int DoubleRoshambo::maxScore(vector<string> a, vector<string> b) {
  
  
}




/* Things Learnt:
Bipartite graph -> graph with disjoint set of vertices
Matching -> set of edges without common vertices
Hungarian Algorithm -> assignment problem

Maximal matching -> A matching is maximal if we cannot add any edge to the existing set
Maximum matching -> Number of edges in the Maximal matching is the highest possible |M| > |M'|

Max Flow -> Augumenting paths

Maxium Flow:
Sink / Source => 

Residual Networks => Take the given path and reverse it. Max out the capacity of the given path (subtracting the given flow) 
Augmenting Paths  => Any path in the residual graph from source to sink
Maximum flow = minimum cut of graph!

Cut:
Capacity of cut => sum of capacities of edged going from A to B
Flow of cut => sum of edges (A to B) - (B to A)
=> Flow < cut; Hence max flow = min cut!

References:
http://en.wikipedia.org/wiki/Matching_(graph_theory)
http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=hungarianAlgorithm
http://www.cs.dartmouth.edu/~ac/Teach/CS105-Winter05/Notes/kavathekar-scribe.pdf
http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=maxFlow
