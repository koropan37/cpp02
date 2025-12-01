#include "Point.hpp"

Point::Point(void) : x(0), y(0) {}

Point::Point(const float x, const float y) : x(x), y(y) {}

Point::Point(const Fixed& x, const Fixed& y) : x(x), y(y) {}

Point::Point(const Point& p) : x(p.x), y(p.y) {}

Point Point::operator=(const Point& p) { return p; }

Point::~Point(void) {}

const Fixed& Point::getX(void)const { return x; }
const Fixed& Point::getY(void)const { return y; }

std::ostream &operator<<(std::ostream &o, const Point &p) {
  o << "(" << p.getX() << "," << p.getY() << ")";
  return o;
}
