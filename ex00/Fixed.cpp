#include "Fixed.hpp"

Fixed::Fixed(void) : raw_(0) {
    std::cout << "Default constructor called" << std::endl; 
}

Fixed::Fixed(const Fixed &raw) {
    std::cout << "Copy constructor called" << std::endl;
    operator=(raw);
}

Fixed& Fixed::operator=(const Fixed &raw) {
    std::cout << "Copy assignment operator called" << std::endl; 
    if(this != &raw) raw_ = raw.getRawBits();
    return *this;
}
//すでに存在しているオブジェクトの中身を書き換える時に使われる
//default(何も書かない場合)はshallow cpoy

//shallow copy（同じメモリ領域を指している) 
//... コピー元のデータに変更を加えるとコピー先も変更される

//deep    copy (違うメモリ両機を指してる)
//... コピー元のデータに変更を加えてもコピー先は変更されない

//if文はメモリなどを確保している時のために必要
//(コピー元のメモリを解放した後にアクセスしてクラッシュする恐れあり)



Fixed::~Fixed(void) {
    std::cout << "Destructor called" << std::endl; 
}

int Fixed::getRawBits(void) const {
    std::cout << "getRawBits member function called" << std::endl; 
    return raw_;
}

void Fixed::setRawBits(int const raw) {
    std::cout << "setRawBits member function called" << std::endl; 
    raw_ = raw;
}
