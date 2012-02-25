#include<iostream>
#include<vector>

using namespace std;


int compute_min_smooth(int n){

  int rValue = 1;
  for(int i = 2; i <= n ; i++) {
    while(n % i == 0) {
      n /= i;
      rValue = i;
    }
  }
  return rValue;
}  


int main() {

  int s;
  cout<<"Enter num:";
  cin>>s;
  cout<<" "<<compute_min_smooth(s)<<endl;

}
