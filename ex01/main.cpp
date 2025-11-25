#include "Fixed.hpp"
#include <iostream>
#include <cstdlib>

int main( void ) {
    try {
        Fixed a;
        Fixed const b( 10 );
        Fixed const c( 42.42f );
        Fixed const d( b );
        a = Fixed( 1234.4321f );
        std::cout << "a is " << a << std::endl;
        std::cout << "b is " << b << std::endl;
        std::cout << "c is " << c << std::endl;
        std::cout << "d is " << d << std::endl;
        std::cout << "a is " << a.toInt() << " as integer" << std::endl;
        std::cout << "b is " << b.toInt() << " as integer" << std::endl;
        std::cout << "c is " << c.toInt() << " as integer" << std::endl;
        std::cout << "d is " << d.toInt() << " as integer" << std::endl;

        Fixed const e( -10 );
        std::cout << "e is " << e << std::endl;
        std::cout << "e is " << e.toInt() << " as integer" << std::endl;

        Fixed const f( -10.35f );
        std::cout << "f is " << f << std::endl;
        std::cout << "f is " << f.toInt() << " as integer" << std::endl;
        // Fixed const g( 2147483467 );
        // std::cout << "g is " << g.toInt() << " as integer" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
//coutのデフォルト表示は有効数字6桁
