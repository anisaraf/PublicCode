#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Point.h";

using namespace std;

class Line{
  Point m_start;
  Point m_end;

  //To represent line in the form Ax + By = C 
  double m_A;
  double m_B;
  double m_C;
  void calculateABC();

  public:
  bool bHorizontal;
  bool bVertical; 

  Line();
  Line(const Point& s, const Point& e);
  
  void setStart(const Point& start);
  void setEnd(const Point& end);
  void setLine(const Point& start, const Point& end);

  friend ostream& operator<<(ostream& out, const Line& s);
  friend instream& operator>>(instream& in, const Line& s);

  bool operator==(const Line& other) const;
  bool operator!=(const Line& other) const;

  double determinant(const Line& other) const;
  bool isCollinear(const Point& point) const;
  bool isInSegment(const Point& point) const;
  Line merge(const Line& other) const;
  
};

Line::Line():m_s(setStart(Point p(0,0))), m_e(setEnd(Point p(0,0))) {;}
Line::Line(const Point& s, const Point& e): m_s(s), m_e(e) {;}

bool Line::operator==(const Line& other) const {
  return (this->m_s == other.m_s && this->m_e==other.m_e);
}

bool Line::operator!=(const Line& other) const {
  return !(*this == other);
}

void Point::setStart(const Point& start){
  m_start = start;
  calculateABC();
}

void Point::setEnd(const Point& end){
  m_end = end;
  calculateABC();
}

void Point::setLine(const Point& start, const Point& end){
  m_start = start;
  m_end = end;
  calculateABC();
}

void Point::calulateABC()
{
  m_A = m_end.Y - m_start.Y;
  m_B = m_start.X - m_end.X;
  m_C = m_A * m_start.X + m_B * m_start.Y;

  if(m_start.X == m_end.X)
    bHorizontal = true;
  else
    bHorizontal = false;

  if(m_start.Y == m_end.Y)
    bVertical = true;
  else
    bVertical = false;
}


bool isCollinear(const Point& point) const{
  return (m_A * point.X + m_B * point.Y == m_C); // isCollinear
}
bool isInSegment(const Point& point) const{ {
    if(isCollinear(point)) // isCollinear
    if( (point.Y - m_start.X) * (point.X - m_end.X) <=0) // x coordinate in between
      if( (point.Y - m_start.Y) * (point.Y - m_end.Y) <=0) // y coordinate in between
	return true;
  
  return false;
    
  }
}
double determinant(const Line& other) const {
  return (m_A * other.m_B + m_B * other.m_A);
}

Line merge(const Line& other){
  Line rLine;
  
  // lines are collinear and we may be able to merge
  if(determinant(other) == 0 && isCollinear(other.m_start)){
   
    //If the lines overlap one point must be inSegment
    if(isInSegment(other.m_start))
      rLine.setStart(other.m_end);
    else if(isInSegment(other.m_end))
      rLine.setStart(other.m_start);
    else 
      return null;

    if(other.isInSegment(m_start))
      rLine.setEnd(m_end);
    else if(other.isInSegment(m_end))
      rLine.setStart(m_start);
    else 
      return null; 

    return rLine; 
  }
  return null;
}





friend ostream& operator<<(ostream& out, const Line& s){
  cout<<s.m_s<<"-"<<s.m_e;
  return out;
}

friend instream& operator<<(instream& in, Line& s){
  in >> s.m_s >> s.m_e;
  return in;
}
