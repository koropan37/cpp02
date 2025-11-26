#ifndef POINT_HPP_
#define POINT_HPP_

#include "Fixed.hpp"

class Point {
 private:
	const Fixed x;
	const Fixed y;
 public:
	Point();
	Point(const float x, const float y);
	Point(const Fixed& x, const Fixed& y);
	Point(const Point& point);
	Point operator=(const Point& point);
	~Point();

	
};

#endif
