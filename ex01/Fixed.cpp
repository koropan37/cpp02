#include "Fixed.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

Fixed::Fixed(void) : raw_(0) {
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &raw) {
    std::cout << "Copy constructor called" << std::endl;
    operator=(raw);
}

Fixed::Fixed(const int& raw) {
    std::cout << "Int constructor called" << std::endl;
    long tmp = static_cast<long>(raw) * (1L << fixed_bit_);

    validateOverflow(tmp);
    raw_ = static_cast<int>(tmp);
}
//(1 << fixed_bit_)fixed_bit_は8で8ビット分シフト == (256)
//後に同じ値で割る

Fixed::Fixed(const float& raw) {
    std::cout << "Float constructor called" << std::endl;
    const double tmp = static_cast<double>(raw) * static_cast<double>(1L << fixed_bit_);

    if(tmp != tmp) throw std::runtime_error("NaN");
	validateOverflow(tmp);
    raw_ = static_cast<int>(roundf(static_cast<float>(tmp)));
}

//NaN(Not a number)0除算や型変換が失敗した場合に発生
//NaN != NaNになる
//roundfは四捨五入(負は0から遠ざける)
//2.5->3.0, -2.5->3.0

Fixed &Fixed::operator=(const Fixed& raw) {
    std::cout << "Copy assignment operator called" << std::endl;
    if(this != &raw) raw_ = raw.getRawBits();
    return *this;
}

Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const { return raw_; }

void Fixed::setRawBits(int const raw) { raw_ = raw; }

float Fixed::toFloat(void) const {
    return (static_cast<float>(getRawBits()) / static_cast<float>(1 << fixed_bit_));
}

int Fixed::toInt(void) const {
    return (getRawBits() / (1 << fixed_bit_));
}

std::ostream &operator<<(std::ostream& out, const Fixed& raw) {
	return out << raw.toFloat();
}
// << aのようなところで呼ばれる

void Fixed::validateOverflow(long v) {
    const long max = static_cast<long>(std::numeric_limits<int>::max());
    const long min = static_cast<long>(std::numeric_limits<int>::min());
    if (v > max) throw std::overflow_error("overflow");
    if (v < min) throw std::overflow_error("underflow");
}

void Fixed::validateOverflow(double v) {
    const double max = static_cast<double>(std::numeric_limits<int>::max());
    const double min = static_cast<double>(std::numeric_limits<int>::min());
    if (v > max + 0.5) throw std::overflow_error("overflow");
    if (v < min - 0.5) throw std::overflow_error("underflow");
}
//オーバーフローをオーバーライドでチェックするためにlong, doubleに変換
