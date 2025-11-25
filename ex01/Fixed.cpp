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
    const int scale = (1 << fixed_bit_);            // 256
    const int max_in = std::numeric_limits<int>::max() / scale;
    const int min_in = std::numeric_limits<int>::min() / scale;

    // 乗算する前に範囲チェックする方式（long long 不要）
    if (raw > max_in) throw std::overflow_error("overflow");
    if (raw < min_in) throw std::overflow_error("underflow");

    raw_ = raw * scale; // 安全に乗算できる
}
//(1 << fixed_bit_)fixed_bit_は8で8ビット分シフト == (256)
//後に同じ値で割る

Fixed::Fixed(const float& raw) {
    std::cout << "Float constructor called" << std::endl;
    const double scale = static_cast<double>(raw) * static_cast<double>(1 << fixed_bit_);

    if (scale != scale)
        throw std::overflow_error("NaN");

    const double max = static_cast<double>(std::numeric_limits<int>::max());
    const double min = static_cast<double>(std::numeric_limits<int>::min());

    if (scale > max + 0.5) throw std::overflow_error("overflow");
    if (scale < min - 0.5) throw std::overflow_error("underflow");

    raw_ = static_cast<int>(roundf(scale));
}

//NaN(Not a number)0除算や型変換が失敗した場合に発生
//NaN != NaNになる
//roundfは最近接整数に丸めた値にする
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
	out << raw.toFloat();
	return out;
}
// << aのようなところで呼ばれる
