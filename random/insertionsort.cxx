#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <limits>

using namespace std;

void bubbleSort(int arr[], size_t size) {
  for (int i = 0; i<size; ++i)
    {
      for (int j = 0; j < i; j++) {
	if(arr[j] > arr[i])
	  swap(arr[i], arr[j]);
      }
    }
}

void insertionSort(int arr[], size_t size) {
  for(int i = 0; i<size; ++i) {
    for(int j = i -1; j >= 0 && arr[j] > arr[j+1]; j--)
      swap(arr[j+1], arr[j]);
  }
}


//pick up and move element till we find the right place for the element
void selectionSort(int arr[], size_t size) {
  for(int i = 0; i < size; ++i) {
    int iPos = i;
    for(int j = i + 1; j < size; j++) {
      if(arr[j] < arr[iPos])
	iPos = j;
    }   
    swap(arr[iPos], arr[i]);
  }
  
}

int main() {
  int arr[] = {-2, 1, -3, 4, -1, 2, 1, -10, 400};
  selectionSort(arr, sizeof(arr)/sizeof(int));

  for (int i = 0; i < sizeof(arr)/sizeof(int); ++i)
    {
      cout<<arr[i]<<" ";
    }
  cout<<endl;
  
}
