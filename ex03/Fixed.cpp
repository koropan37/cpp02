#include "Fixed.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

Fixed::Fixed(void) : raw_(0) {}

Fixed::Fixed(const Fixed& raw) {
    operator=(raw);
}

Fixed::Fixed(const int& raw) {
    long tmp = static_cast<long>(raw) * (1L << fixed_bit_);

    validateOverflow(tmp);
    raw_ = static_cast<int>(tmp);
}

Fixed::Fixed(const float& raw) {
    const double tmp = static_cast<double>(raw) * static_cast<double>(1L << fixed_bit_);

    if(tmp != tmp) throw std::runtime_error("NaN");

	validateOverflow(tmp);

    raw_ = static_cast<int>(roundf(static_cast<float>(tmp)));
}

Fixed &Fixed::operator=(const Fixed& raw) {
    if(this != &raw) raw_ = raw.getRawBits();
    return *this;
}

Fixed::~Fixed(void) {}

int Fixed::getRawBits(void) const { return raw_; }

void Fixed::setRawBits(int const raw) { raw_ = raw; }

float Fixed::toFloat(void) const {
    return (static_cast<float>(getRawBits()) / static_cast<float>(1L << fixed_bit_));
}

int Fixed::toInt(void) const {
    return (getRawBits() / (1L << fixed_bit_));
}

std::ostream &operator<<(std::ostream& out, const Fixed& raw) {
	return out << raw.toFloat();
}

bool Fixed::operator>(const Fixed& other)const { return raw_ > other.raw_; }
bool Fixed::operator<(const Fixed& other)const { return raw_ < other.raw_; }
bool Fixed::operator>=(const Fixed& other)const { return raw_ >= other.raw_; }
bool Fixed::operator<=(const Fixed& other)const { return raw_ <= other.raw_; }
bool Fixed::operator==(const Fixed& other)const { return raw_ == other.raw_; }
bool Fixed::operator!=(const Fixed& other)const { return raw_ != other.raw_; }

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


Fixed Fixed::operator+(const Fixed& other)const {
	long tmp = \
				static_cast<long>(this->raw_) \
			  + static_cast<long>(other.raw_);

	validateOverflow(tmp);

	Fixed res;
	res.setRawBits(static_cast<int>(tmp));
	return res;
}

Fixed Fixed::operator-(const Fixed& other)const {
	long tmp = \
				static_cast<long>(this->raw_) \
			  - static_cast<long>(other.raw_);

	validateOverflow(tmp);

	Fixed res;
	res.setRawBits(static_cast<int>(tmp));
	return res;
}

Fixed Fixed::operator*(const Fixed& other)const {

    double tmp = \
				  static_cast<double>(this->raw_) \
				* static_cast<double>(other.raw_) \
				/ static_cast<double>(1 << fixed_bit_);
	validateOverflow(tmp);
    Fixed res;
    res.setRawBits(static_cast<int>(roundf(static_cast<float>(tmp))));
    return res;
}


Fixed Fixed::operator/(const Fixed& other)const {
	if(other.raw_ == 0) throw std::runtime_error("division by zero"); //0除算チェック
    double tmp = \
				 (static_cast<double>(this->raw_) \
				* static_cast<double>(1 << fixed_bit_)) \
				/ static_cast<double>(other.raw_);
	validateOverflow(tmp);

	Fixed res;
	res.setRawBits(static_cast<int>(roundf(static_cast<float>(tmp))));
	return res;
}

Fixed& Fixed::operator++(void) { //前置(++i)
	++raw_;
	return *this;
}

Fixed Fixed::operator++(int) { //後置(i++)
	Fixed tmp(*this);
	raw_++;
	return tmp;
}

Fixed& Fixed::operator--(void) { //前置(--i)
	--raw_;
	return *this;
}

Fixed Fixed::operator--(int) { //後置(i++)
	Fixed tmp(*this);
	raw_--;
	return tmp;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
    return (a >= b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
    return (a >= b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
    return (a <= b) ? a : b;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
    return (a <= b) ? a : b;
}
