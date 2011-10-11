#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

struct node {
  char data;
  node* links[26];
};


void buildTrie  (const string& s, node* root,int depth) {
  if(depth ==0 ) return;
  for(int i = 0; i<s.length(); ++i){
    root->links[i] = new node;
    root->links[i]->data = s[i];
    buildTrie(s,root->links[i], depth - 1);
  }
}


void printTrie(node* root, const string& prefix) {

  cout<<prefix<<root->data<<"\n";
  for(int i=0; i < 26; ++i) {
    if(root->links[i]) {
      printTrie(root->links[i], prefix + root->data);
    }
  }
}


int main(int argc, char* argv[]) {

  node root;
  root.data = ' ';
  buildTrie("t", &root, 1);
  printTrie(&root, "");

}
