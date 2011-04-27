#include <sstream>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Integer point only !
class Point{
 public:
  double X;
  double Y;
  
  Point();
  Point(double x, double y);
  friend ostream& operator<< (ostream& out, const Point& p);
  friend istream& operator>> (istream& in, Point& p);
  
  bool operator==(const Point& other) const;
  bool operator!=(const Point& other) const;
  bool operator<(const Point& other) const;
  bool operator<=(const Point& other) const;

  Point swapXY() const;
};

Point::Point():X(0),Y(0){;}
Point::Point(double x, double y):X(x),Y(y){;}

ostream& operator<<(ostream& out, const Point& p){
  out<<"("<<p.X<<","<<p.Y<<")";
  return out;
}

istream& operator>>(istream& in, Point& p){
  in >> p.X >> p.Y;
  return in;
}

bool Point::operator==(const Point& other) const{
  return (this->X == other.X && this->Y == other.Y);
}

bool Point::operator!=(const Point& other) const{
  return !(*this==other);
}

bool Point::operator<(const Point& other) const {
  if(X < other.X)
    return true;
  else
    if(X == other.X)
      return (Y < other.Y);
    else
      return false;
}

bool Point::operator<=(const Point& other) const {
  return (*this < other || *this == other);
}

Point Point::swapXY() const{
  return Point(Y,X);
}
