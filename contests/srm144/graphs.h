#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <queue>

using namespace std;

template <class T>
class Graph {
 
  
public:
  
  typedef set<T> edges;
  typedef  map<T, edges > map_graph; 
  typedef typename map<T, edges >::iterator iterator;  
  
 
  Graph(bool directed = false): m_directed(directed) {;}
  iterator  begin() { return m_vertices.begin(); }
  iterator  end() { return m_vertices.end() ;} 
  
  int size() {return m_vertices.size();}

  void insertEdge(T n1, T n2);
  void insertVertex(const T& v);
  void insertVertex( iterator it);
  edges getEdges(iterator v);
  int numOddVertices();

  vector< Graph<T> > getConnectedGraphs();
  friend ostream& operator<<(ostream& out, Graph<T>& g)
  {
    for(Graph::iterator it = g.begin(); it != g.end(); ++it)
      {
	//for(typename edges::iterator it_e = it->second.begin(); it_e != it->second.end(); ++it_e)
	out<<it->first<< " E:" ;//<< "-> " <<*it_e<<",";
	
	copy(it->second.begin(), it->second.end(), ostream_iterator<T>(out));
	cout <<endl;
      }
    return out;
  }

private:
  map_graph m_vertices;
  bool m_directed;
};


template<class T> void Graph<T>::insertVertex(iterator it){  
  iterator g_it = m_vertices.find(it->first);
  if(g_it != this->end())
    m_vertices.erase(g_it);
  
  m_vertices.insert(pair<T, edges>(it->first, it->second));    
}

template<class T> void Graph<T>::insertVertex(const T& v){
  edges temp;
  m_vertices.insert(make_pair(v,temp));
}


template<class T> void Graph<T>::insertEdge(T v1, T v2){
  edges temp;
  iterator  v_s= m_vertices.insert(m_vertices.begin(), pair<T, edges >(v1, temp));
  iterator v_e = m_vertices.insert(m_vertices.begin(), pair<T, edges >(v2, temp));
  
  v_s->second.insert((v_e->first));
  if(!m_directed)
      v_e->second.insert((v_s->first));
}

template<class T>
typename Graph<T>::edges Graph<T>::getEdges(iterator it)
{
  if(it)
    return it->second;
  
  return NULL;
}


template<class T> vector< Graph<T> > Graph<T>::getConnectedGraphs()
{
  
  Graph g_copy(*this);
  vector< Graph<T> > rv;
 
  while(g_copy.size() > 0) {
  
    Graph<T> g;
    queue<T> q;
    iterator temp= g_copy.begin();
    q.push(temp->first);
    
    while(q.size() > 0) {
      T curr = q.front();
      iterator curr_it = g_copy.m_vertices.find(curr);
      if(curr_it == g_copy.m_vertices.end()) {q.pop();continue;} // already visited
    
      g.insertVertex(curr_it);
      edges e= curr_it->second;
      //if(e == e.end()  continue;
      for (typename edges::iterator it_edges = e.begin(); it_edges != e.end() ; ++it_edges)	
	q.push(*it_edges);
      
      g_copy.m_vertices.erase(curr_it); 
      q.pop();
    }

    rv.push_back(g);
  }
  return rv;
}



template<class T> int Graph<T>::numOddVertices(){
  int rValue = 0;
  for(Graph::iterator it = this->begin() ; it != this->end(); ++it)
    if( (it->second).size() % 2 != 0 ) 
      rValue++;
  
  return rValue; 
  
}

