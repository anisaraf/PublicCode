#include<iostream>
#include<limits.h>

using namespace std;

struct node {
  int data;
  node* left;
  node* right;
} r;



bool isBinaryTree(node* root, int last) {

  cout<<"last: "<<last<<endl;
  if(!root) return true;
 
  bool val = isBinaryTree(root->left, last);
  if( root->data < last || !val )
    return false;
  else {
    last = root->data;
    cout<<" "<<root->data;
  }

  return isBinaryTree(root->right, last);
}

node* insertNode(node* nodes, int data) {

  if(!nodes) {
    node* newNode = new node;
    newNode->data = data;
    newNode->left = 0;
    newNode->right = 0;
    
    return newNode;
  }
  else{
    if( data <= nodes->data)
      nodes->left = insertNode(nodes->left, data);
    else
      nodes->right = insertNode(nodes->right, data);
    
    return (nodes);
  }
}


void makeBinaryTree(node* root, int* arr, int arrLen) {
  for(int i = 0; i < arrLen; ++i){
    cout<<"inserting"<<arr[i]<<endl;
    insertNode(root, arr[i]);
  }
}


int main() {

  int a[] = {1,4,5,6,7,8,2,3,5};

  r.data = 6;

  makeBinaryTree(&r, a, 9);

  cout<<isBinaryTree(&r, INT_MIN)<<endl;

}
