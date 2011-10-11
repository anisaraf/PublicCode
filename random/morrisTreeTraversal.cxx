#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;
/* A binary tree tNode has data, pointer to left child
   and a pointer to right child */
struct tNode
{
  int data;
  struct tNode* left;
  struct tNode* right;
};
/* Function to traverse binary tree without recursion and
   without stack */
void MorrisTraversal(struct tNode *root)
{
  tNode* current = root; 
  while(current){
    if(!current->left){
      cout<<current->data<<" ";
      current = current->right;
    } else {
      tNode* pre = current->left;
      while(pre->right && pre->right != current)
	pre = pre->right;
      if(!pre->right) {
	pre->right = current;
	current = current->left;
      } else {
	cout<<current->data<<" ";
	current = current->right;
	pre->right = NULL;
      }
    }
  }
}

/* UTILITY FUNCTIONS */
/* Helper function that allocates a new tNode with the
   given data and NULL left and right pointers. */
struct tNode* newtNode(int data)
{
  struct tNode* tNode = (struct tNode*)
    malloc(sizeof(struct tNode));
  tNode->data = data;
  tNode->left = NULL;
  tNode->right = NULL;
  return(tNode);
}
/* Driver program to test above functions*/
int main()
{
  /* Constructed binary tree is
     1
     /   \
     2      3
     /  \
     4     5
  */
  struct tNode *root = newtNode(1);
  root->left        = newtNode(2);
  root->right       = newtNode(3);
  root->left->left  = newtNode(4);
  root->left->right = newtNode(5);
  MorrisTraversal(root);
  getchar();
  return 0;
}
