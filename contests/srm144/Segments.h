#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Point.h"
#include <assert.h>

using namespace std;

class Line{
 private:
  bool  m_Horizontal;
  Point m_start;
  Point m_end;
 
public:
  Line(const string&);
  Line(const Point& x, const Point& y);
  
  void makeLine(const Point& x, const Point& y);
  
  Point getStart() const {  return isHorizontal() ? m_start : m_start.swapXY();}
  Point getEnd() const {  return isHorizontal() ? m_end : m_end.swapXY();}
  bool  isHorizontal() const {return m_Horizontal;}
  
  bool  isOverlap(const Line&) const;
  bool  merge(const Line&, Line&) const;
  bool  intersection(const Line&, Point&) const;
  bool  isPointOnSegment(const Point& point) const;
  
  bool  operator==(const Line&) const;
  bool  operator!=(const Line&) const;
  friend ostream& operator<<(ostream&, const Line&);
  friend istream& operator>>(istream&, Line&);
};

bool Line::operator==(const Line& other) const{
  return (this->m_start == other.m_start && this->m_end == other.m_end && isHorizontal() == other.isHorizontal());
}

bool Line::operator!=(const Line& other) const{
  return !(*this==other);
}


Line::Line(const string& szPoints){
  Point start, end;
  istringstream in(szPoints);
  in>>start>>end;
  makeLine(start,end);
}

Line::Line(const Point& start, const Point& end){
  makeLine(start, end);
}


void Line::makeLine(const Point& start, const Point& end)
{

  assert(start.X == end.X || start.Y == end.Y);
  m_start = start;
  m_end = end;
 
  m_Horizontal = start.Y == end.Y ? true : false;
 
  //make points horizontal to ease all calculations
  if(!isHorizontal()){
    m_start = m_start.swapXY();
    m_end = m_end.swapXY();
  }
  
  //always set start < end as defined by Point
  if(m_end < m_start)
    swap(m_start, m_end);
}

bool Line::isOverlap(const Line& other) const{
  // not in same axis
  if( ( isHorizontal() != other.isHorizontal()))
    return false;
  return (isPointOnSegment(other.getStart()) || other.isPointOnSegment(getStart()));  
}


bool Line::isPointOnSegment(const Point& point) const
{
  Point p(point);
  if(!isHorizontal()) p =  p.swapXY(); 
  return (p.Y == m_start.Y && m_start.X <= p.X && p.X <= m_end.X); 
}


bool Line::intersection(const Line& other, Point& inPoint) const{ 
  if( isHorizontal() == other.isHorizontal()) return false;
  inPoint.X = isHorizontal() ? other.m_start.Y : m_start.Y;
  inPoint.Y = isHorizontal() ? m_start.Y : other.m_start.Y;
  
  // return true only if intersection is not out of segment
  return isPointOnSegment(inPoint);
}

bool Line::merge(const Line& other, Line& inLine) const{
  if(!isOverlap(other)) return false;
  Point start = min(m_start, other.m_start);
  Point end = max(m_end, other.m_end);
  inLine = isHorizontal() ?  Line(start, end): Line(start.swapXY(), end.swapXY());
  return true;
}

ostream& operator<<(ostream& out, const Line& s){
  if(s.isHorizontal())
     cout<<"{"<<s.m_start<<","<<s.m_end<<"},"; //<<s.isHorizontal();
  //cout<<s.m_start<<"-"<<s.m_end<<":"<<s.isHorizontal();
  else
    cout<<"{"<<s.m_start.swapXY()<<","<<s.m_end.swapXY()<<"},"; //<<s.isHorizontal();
  return out;
}

istream& operator>>(istream& in, Line& s){
  Point start, end;
  in>>start>>end;
  s = Line(start,end);
  return in;
}


//http://softsurfer.com/Archive/algorithm_0301/algorithm_0301.htm#Point Functions
//
