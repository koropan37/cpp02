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
	Point(const Point& p);
	Point operator=(const Point& p);
	~Point();

	const Fixed& getX()const ;
	const Fixed& getY()const ;
};

bool bsp( Point const a, Point const b, Point const c, Point const p);

#endif
