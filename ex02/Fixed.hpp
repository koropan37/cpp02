#ifndef FIXED_HPP_
#define FIXED_HPP_

#include <iostream>
#include <string>

class Fixed {
 private:
    int raw_;
    static const int fixed_bit_ = 8;

    static void validateOverflow(long v);
    static void validateOverflow(double v);

 public:
    Fixed();
	Fixed(const int& raw);
	Fixed(const float& raw);
    Fixed(const Fixed& raw);
    Fixed& operator=(const Fixed& raw);
    ~Fixed();

    int     getRawBits(void) const;
    void    setRawBits(int const raw);

	float 	toFloat(void) const;
	int 	toInt(void) const;

    bool operator>(const Fixed& other)const;
    bool operator<(const Fixed& other)const;
    bool operator>=(const Fixed& other)const;
    bool operator<=(const Fixed& other)const;
    bool operator==(const Fixed& other)const;
    bool operator!=(const Fixed& other)const;

    Fixed operator+(const Fixed& other)const;
    Fixed operator-(const Fixed& other)const;
    Fixed operator*(const Fixed& other)const;
    Fixed operator/(const Fixed& other)const;

    Fixed& operator++(void);
    Fixed  operator++(int);
    Fixed& operator--(void);
    Fixed  operator--(int);

    static const Fixed& max(const Fixed& a, const Fixed& b);
    static       Fixed& max(Fixed& a, Fixed& b);
    static const Fixed& min(const Fixed& a, const Fixed& b);
    static       Fixed& min(Fixed& a, Fixed& b);

};

std::ostream &operator<<(std::ostream &out, const Fixed &raw);

#endif
