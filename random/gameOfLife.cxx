#include<iostream>
#include<stdlib.h>
#include<time.h>

using namespace std;

class GameOfLife {
  int** m_display;
  int** m_temp;
  int m_height;
  int m_width;


public:
  GameOfLife(int height, int width): m_height(height), m_width(width) {

    m_display = new int*[m_height];
    m_temp = new int*[m_height];

    for(int i =0; i < m_height; ++i) {
      m_display[i] = new int[m_width];
      m_temp[i] = new int[m_width];
      
      for(int j =0; j < m_width; ++j){
	m_display[i][j] = rand() % 2;
      }
    }
  }

  void next_gen(){
    for(int i = 0; i < m_height; ++i)
      for(int j=0; j < m_width; ++j) {
	int nc = 
          m_display[(i - 1 + m_height) % m_height][(j-1 + m_width) % m_width] +
	  m_display[(i - 1 + m_height) % m_height][(j   + m_width) % m_width] +
	  m_display[(i - 1 + m_height) % m_height][(j+1 + m_width) % m_width] +
	  m_display[i][(j-1 + m_width) % m_width] +
	  m_display[i][(j+1 + m_width) % m_width] +
	  m_display[(i + 1 + m_height) % m_height][(j-1 + m_width) % m_width] +
	  m_display[(i + 1 + m_height) % m_height][j] +
	  m_display[(i + 1 + m_height) % m_height][ (j +1 + m_width) % m_width];
	

	if(nc < 2 || nc > 3
)	  m_temp[i][j] = 0;
	else if(nc == 2) 
	  m_temp[i][j] = m_display[i][j];
	else
	  m_temp[i][j] = 1;
      }
    
    int** temp;
    temp = m_display;
    m_display = m_temp;
    m_temp = temp;
  }

  void print_display() {
    for(int i = 0; i < m_height; ++i){
      cout<<endl;
      for(int j=0; j < m_width; ++j) {
	cout<<m_display[i][j]<<" ";
      }
    }

    cout<<"\n End of gen \n\n";
  }

};


int main(){
  GameOfLife g(5,5);
  g.print_display();
  g.next_gen();
  g.print_display();
  g.next_gen();
  g.print_display();
  g.next_gen();
  g.print_display();
}
