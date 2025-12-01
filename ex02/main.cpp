#include <iostream>
#include <iomanip>
#include <exception>
#include <cmath>
#include "Fixed.hpp"


void testFromSubjects();
void testOperators();
static void testCalculate(void) ;

int main() {
	testFromSubjects();
	testOperators();
	testCalculate();
    return 0;
}

//
// プロパティ				float の値			double の値
// 表現可能な最大の数値	   	  3.402823466e+38	 1.7976931348623157e+308
// 精度を失わない最小の数値	   1.175494351e-38	  2.2250738585072014e-308
// 表現可能な最小の数値(*)	  1.401298464e-45	 5e-324
// 仮数ビット				23					52
// 指数ビット				8					11
// イプシロン(**)			1.1929093e-7	    2.220446049250313e-16

// イプシロンは、1+x > 1 となる最小の x

void printTitle(std::string const &title) {
  // set color to green
  std::cout << "\033[1;32m";
  // print '='
  std::cout << std::setfill('=') << std::setw(80) << "" << std::endl;
  // print title at the center
  std::cout << std::setfill(' ') << std::setw(40 - title.length() / 2) << ""
            << title << std::endl;
  // print '='
  std::cout << std::setfill('=') << std::setw(80) << "" << std::endl;
  // reset color
  std::cout << "\033[0m" << std::setfill(' ') << std::setw(0);
}

void testFromSubjects() {
  printTitle("Tests from subject's pdf");
  Fixed a;
  Fixed const b(Fixed(5.05f) * Fixed(2));
  std::cout << a << std::endl;
  std::cout << ++a << std::endl;
  std::cout << a << std::endl;
  std::cout << a++ << std::endl;
  std::cout << a << std::endl;
  std::cout << a / Fixed(0.5f) << std::endl;
  std::cout << b << std::endl;
  std::cout << Fixed::max(a, b) << std::endl;
}

void testOperators() {
  {
    Fixed a;
    Fixed b(1);
    const Fixed c(0.1f);
    const Fixed d(0.01f);
	printTitle("Next");
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    // setRawBits / getRawBits
    printTitle("setRawBits / getRawBits");
    std::cout << "a.setRawBits(-1): " << std::endl;
    a.setRawBits(-1);
    std::cout << "a: " << a << std::endl;
    std::cout << "a.toInt(): " << a.toInt() << std::endl;
    std::cout << "a.toFloat(): " << a.toFloat() << std::endl;
    std::cout << "a.getRawBits(): " << a.getRawBits() << std::endl;
    // getRawBits()の返り値はintなのでFixedのoperator<<は呼ばれない
    // Comparison Operator
    printTitle("Comparison Operator");
    std::cout << "a < b " << std::endl;
    std::cout << std::boolalpha << (a < b) << std::endl;
    std::cout << "a > b" << std::endl;
    std::cout << std::boolalpha << (a > b) << std::endl;
    std::cout << "a <= b" << std::endl;
    std::cout << std::boolalpha << (a <= b) << std::endl;
    std::cout << "a >= b" << std::endl;
    std::cout << std::boolalpha << (a >= b) << std::endl;
    std::cout << "a == b" << std::endl;
    std::cout << std::boolalpha << (a == b) << std::endl;
    std::cout << "a != b" << std::endl;
    std::cout << std::boolalpha << (a != b) << std::endl;
    std::cout << "c < d" << std::endl;
    std::cout << std::boolalpha << (c < d) << std::endl;
    std::cout << "c > d" << std::endl;
    std::cout << std::boolalpha << (c > d) << std::endl;
    std::cout << "c <= d" << std::endl;
    std::cout << std::boolalpha << (c <= d) << std::endl;
    std::cout << "c >= d" << std::endl;
    std::cout << std::boolalpha << (c >= d) << std::endl;
    std::cout << "c == d" << std::endl;
    std::cout << std::boolalpha << (c == d) << std::endl;
    std::cout << "c != d" << std::endl;
    std::cout << std::boolalpha << (c != d) << std::endl;
    // Arithmetic Operation
    printTitle("Arithmetic Operator");
    std::cout << "a + b " << std::endl;
    std::cout << a + b << std::endl;
    std::cout << "a - b" << std::endl;
    std::cout << a - b << std::endl;
    std::cout << "a * b" << std::endl;
    std::cout << a * b << std::endl;
    std::cout << "a / b" << std::endl;
    std::cout << a / b << std::endl;
    std::cout << "c + d" << std::endl;
    std::cout << c + d << std::endl;
    std::cout << "c - d" << std::endl;
    std::cout << c - d << std::endl;
    std::cout << "c * d" << std::endl;
    std::cout << c * d << std::endl;
    std::cout << "c / d" << std::endl;
    std::cout << c / d << std::endl;
    // Increment / Decrement
    printTitle("Increment / Decrement");
    std::cout << "++a " << std::endl;
    std::cout << ++a << std::endl;
    std::cout << a << std::endl;
    std::cout << "a++" << std::endl;
    std::cout << a++ << std::endl;
    std::cout << a << std::endl;
    std::cout << "--a" << std::endl;
    std::cout << --a << std::endl;
    std::cout << a << std::endl;
    std::cout << "a--" << std::endl;
    std::cout << a-- << std::endl;
    std::cout << a << std::endl;
    // Overloaded member function
    printTitle("Overloaded member function");
    std::cout << "max(a, b) " << std::endl;
    std::cout << Fixed::max(a, b) << std::endl;
    std::cout << "min( a, b )" << std::endl;
    std::cout << Fixed::min(a, b) << std::endl;
    std::cout << "max( c, d )" << std::endl;
    std::cout << Fixed::max(c, d) << std::endl;
    std::cout << "min( c, d )" << std::endl;
    std::cout << Fixed::min(c, d) << std::endl;
  }
}

static void printResult(const char* label, const Fixed &res) {
    std::cout << std::left << std::setw(16) << label << " : "
              << std::fixed << std::setprecision(6) << res.toFloat() << std::endl;
}

static void testMul(const char* label, const Fixed &a, const Fixed &b) {
    try {
        Fixed r = a * b;
        printResult(label, r);
    } catch (const std::exception &e) {
        std::cout << std::left << std::setw(16) << label << " : " << e.what() << std::endl;
    }
}

static void testDiv(const char* label, const Fixed &a, const Fixed &b) {
    try {
        Fixed r = a / b;
        printResult(label, r);
    } catch (const std::exception &e) {
        std::cout << std::left << std::setw(16) << label << " : " << e.what() << std::endl;
    }
}

static const int SCALE = 1 << 8; // 256

static int raw_int(int v) { return v * SCALE; }
static int raw_float(float v) { return static_cast<int>(roundf(v * static_cast<float>(SCALE))); }

static int mul_raw(int ra, int rb) {
    double tmp = static_cast<double>(ra) * static_cast<double>(rb) / static_cast<double>(SCALE);
    return static_cast<int>(roundf(static_cast<float>(tmp)));
}

static int div_raw(int ra, int rb) {
    double tmp = static_cast<double>(ra) * static_cast<double>(SCALE) / static_cast<double>(rb);
    return static_cast<int>(roundf(static_cast<float>(tmp)));
}

static void print_label(const char* label, int raw) {
    double out = static_cast<double>(raw) / SCALE;
    std::cout << std::left << std::setw(16) << label << " : "
              << std::fixed << std::setprecision(6) << out << std::endl;
}

static void testCalculate(void) {

	int i2 = raw_int(2);
    int i3 = raw_int(3);
    int i_n1 = raw_int(-1);

    int f_0_5 = raw_float(0.5f);
    int f_0_1 = raw_float(0.1f);
    int f_n0_3 = raw_float(-0.3f);
    int f_1_1 = raw_float(1.1f);
    int f_0_3 = raw_float(0.3f);
    int f_1_004 = raw_float(1.004f);
    int f_2_5 = raw_float(2.5f);
    int f_1_25 = raw_float(1.25f);
    int f_0_125 = raw_float(0.125f);
    int f_10_004 = raw_float(10.004f);
	int i_n1_5 = raw_float(-1.5f);
	int f_0_8 = raw_float(0.8f);
	int f_1_33 = raw_float(1.33f);
	int f_2_33 = raw_float(2.33f);
	int f_4_004 = raw_float(4.004f);

    int f_0x400001 = raw_int(0x400001);
    int f_0x200001 = raw_int(0x200001);
    int f_0x100001 = raw_int(0x100001);

    printTitle("Calculation");
	testDiv("2 / 3", Fixed(2), Fixed(3));
    testDiv("3 / 2", Fixed(3), Fixed(2));
    testDiv("2 / 0.5", Fixed(2), Fixed(0.5f));
    testDiv("3 / 0.1", Fixed(3), Fixed(0.1f));
    testDiv("-1 / 2", Fixed(-1), Fixed(2));
    testDiv("1.1 / -0.3", Fixed(1.1f), Fixed(-0.3f));

    testMul("-1 * 2", Fixed(-1), Fixed(2));
    testMul("-1.5 * 2", Fixed(-1.5f), Fixed(2));
    testMul("1.1 * -0.3", Fixed(1.1f), Fixed(-0.3f));
    testMul("1.1 * 0.3", Fixed(1.1f), Fixed(0.3f));
    testMul("1.004 * 1.004", Fixed(1.004f), Fixed(1.004f));
    testMul("2.5 * 1.25", Fixed(2.5f), Fixed(1.25f));
    testMul("0.125 * 2.5", Fixed(0.125f), Fixed(2.5f));
    testMul("10.004 * 0.8", Fixed(10.004f), Fixed(0.8f));

    testMul("0x400001 * 1.33", Fixed(0x400001), Fixed(1.33f));
    testMul("0x200001 * 2.33", Fixed(0x200001), Fixed(2.33f));
    testMul("0x100001 * 4.004", Fixed(0x100001), Fixed(4.004f));

	printTitle("Actual value");
    print_label("2 / 3", div_raw(i2, i3));
    print_label("3 / 2", div_raw(i3, i2));
    print_label("2 / 0.5", div_raw(i2, f_0_5));
    print_label("3 / 0.1", div_raw(i3, f_0_1));
    print_label("-1 / 2", div_raw(i_n1, i2));
    print_label("1.1 / -0.3", div_raw(f_1_1, f_n0_3));

    print_label("-1 * 2", mul_raw(i_n1, i2));
    print_label("-1.5 * 2", mul_raw(i_n1_5, i2));
    print_label("1.1 * -0.3", mul_raw(f_1_1, f_n0_3));
    print_label("1.1 * 0.3", mul_raw(f_1_1, f_0_3));
    print_label("1.004 * 1.004", mul_raw(f_1_004, f_1_004));
    print_label("2.5 * 1.25", mul_raw(f_2_5, f_1_25));
    print_label("0.125 * 2.5", mul_raw(f_0_125, f_2_5));
    print_label("10.004 * 0.8", mul_raw(f_10_004, f_0_8));

    print_label("0x400001 * 1.33", mul_raw(f_0x400001, f_1_33));
    print_label("0x200001 * 2.33", mul_raw(f_0x200001, f_2_33));
    print_label("0x100001 * 4.004", mul_raw(f_0x100001, f_4_004));
}
