#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Fixed.hpp"
#include "Point.hpp"

// print title in green color surrounded by '='
void printTitle(std::string const& title) {
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

// Print triangle with points A, B, C, and P.
void printTriangle(const Point a, const Point b, const Point c, const Point p) {
  // get min and max of x and y
  long minX = std::min(std::min(a.getX(), b.getX()), c.getX()).getRawBits();
  long maxX = std::max(std::max(a.getX(), b.getX()), c.getX()).getRawBits();
  long minY = std::min(std::min(a.getY(), b.getY()), c.getY()).getRawBits();
  long maxY = std::max(std::max(a.getY(), b.getY()), c.getY()).getRawBits();

  // get size of the triangle
  long width = maxX - minX;
  long height = maxY - minY;
  long size = std::max(width, height);
  if (size == 0) size = 1;

  // convert to 10x10 grid
  int ax = (a.getX().getRawBits() - minX) * 10 / size;
  int ay = (a.getY().getRawBits() - minY) * 10 / size;
  int bx = (b.getX().getRawBits() - minX) * 10 / size;
  int by = (b.getY().getRawBits() - minY) * 10 / size;
  int cx = (c.getX().getRawBits() - minX) * 10 / size;
  int cy = (c.getY().getRawBits() - minY) * 10 / size;
  int px = (p.getX().getRawBits() - minX) * 10 / size;
  int py = (p.getY().getRawBits() - minY) * 10 / size;

  // print triangle
  bool printed = false;
  for (int y = 10; y >= 0; y--) {
    for (int x = 0; x <= 10; x++) {
      if (!printed) std::cout << " ";
      if (x == ax && y == ay) {
        std::cout << "A";
      } else if (x == bx && y == by) {
        std::cout << "B";
      } else if (x == cx && y == cy) {
        std::cout << "C";
      } else if (x == px && y == py) {
        std::cout << "P";
        // if point is on the edge of the triangle
      } else if (((y - ay) * (bx - ax) == (by - ay) * (x - ax)) &&
                 x >= std::min(ax, bx) && x <= std::max(ax, bx) &&
                 y >= std::min(ay, by) && y <= std::max(ay, by)) {
        std::cout << ".";
      } else if (((y - by) * (cx - bx) == (cy - by) * (x - bx)) &&
                 x >= std::min(bx, cx) && x <= std::max(bx, cx) &&
                 y >= std::min(by, cy) && y <= std::max(by, cy)) {
        std::cout << ".";
      } else if (((y - cy) * (ax - cx) == (ay - cy) * (x - cx)) &&
                 x >= std::min(cx, ax) && x <= std::max(cx, ax) &&
                 y >= std::min(cy, ay) && y <= std::max(cy, ay)) {
        std::cout << ".";
      } else {
        std::cout << " ";
      }
      if ((x == ax && y == ay) + (x == bx && y == by) + (x == cx && y == cy) +
              (x == px && y == py) >
          1) {
        std::cout << "*";
        printed = true;
      } else {
        printed = false;
      }
    }
    std::cout << std::endl;
  }
}

void test(const std::string& info, const Point a, const Point b, const Point c,
          const Point p) {
  printTriangle(a, b, c, p);

  bool res = bsp(a, b, c, p);

  std::cout << std::fixed << std::setprecision(6);
  std::cout << info << " : " << p << " in A:" << a <<" B:"<< b <<" C:" << c << "\n";
  std::cout << " bsp=" << std::boolalpha << res << std::noboolalpha << "\n";
}

int main(void) {
  {
    Fixed a;
    printTitle("setRawBits / getRawBits");
    std::cout << "a.setRawBits(-1): " << std::endl;
    a.setRawBits(-1);
    std::cout << "a: " << a << std::endl;
    std::cout << "a.toInt(): " << a.toInt() << std::endl;
    std::cout << "a.toFloat(): " << a.toFloat() << std::endl;
    std::cout << "a.getRawBits(): " << a.getRawBits() << std::endl;
  }
  {
    Point p;

    printTitle("ZERO TEST");
    test("...", Point(), Point(), Point(), p);
  }
  {
    Point p;

    printTitle("NORMAL TEST");
    test("On the same line", Point(0, 0), Point(1, 1), Point(3, 3),
         Point(2, 2));
    test("/_._\\", Point(0, 1), Point(-1, 0), Point(1, 0), p);
    test(".\\|", Point(0, 1), Point(1, 1), Point(1, 0), p);
    test(".//", Point(-1, -1), Point(1, 1), Point(1, 0), p);

    test("\\./", Point(1, 1), Point(0, -1), Point(-1, 1), p);
    test("<.|", Point(1, 1), Point(-1, 0), Point(1, -1), p);
    test("|.>", Point(-0.125f, -0.125f), Point(0.125f, -0.125f),
         Point(0, 0.125f), p);
    test("/./", Point(-4242, -1), Point(0, 1), Point(4242, 0), p);

    test("P at vertex A", Point(0,0), Point(5,0), Point(0,5), Point(0,0));
    test("P on edge AB", Point(0,0), Point(5,0), Point(0,5), Point(2.5f, 0.0f));
    test("P on edge BC", Point(0,0), Point(5,0), Point(0,5), Point(3.0f, 2.0f));
    test("P on edge CA", Point(0,0), Point(5,0), Point(0,5), Point(0.0f, 2.0f));
    test("Colinear triangle (degenerate)", Point(0,0), Point(1,1), Point(2,2), Point(1,1));
    test("Two points equal (degenerate)", Point(0,0), Point(0,0), Point(1,0), Point(0,0));
    test("Very small triangle (precision test)", Point(0.0f,0.0f), Point(0.0039f,0.0f), Point(0.0f,0.0039f), Point(0.001f,0.001f));
    test("Large coords", Point(1000,1000), Point(2000,1000), Point(1000,2000), Point(1500,1500));
    test("Outside near edge", Point(0,0), Point(5,0), Point(0,5), Point(2.6f, -0.1f));
  }
  return 0;
}
