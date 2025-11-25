#ifndef FIXED_HPP_
#define FIXED_HPP_

#include <iostream>
#include <string>

class Fixed {
 private:
    int raw_;
    static const int fixed_bit_ = 8;

 public:
    Fixed();
    Fixed(const Fixed &raw);
    Fixed& operator=(const Fixed &raw);
    ~Fixed();

    int     getRawBits(void) const;
    void    setRawBits(int const raw);

};

#endif
