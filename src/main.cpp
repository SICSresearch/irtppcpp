#include <iostream>
#include <estimation/emestimation.h>

using namespace irtpp;
using std::cout;
using std::endl;

int main(int argc, char ** argv)
{
  emestimation em1(argv[1], new onepl());
  emestimation em2(argv[1], new twopl());
  emestimation em3(argv[1], new threepl());

  em1.estimate();
  em2.estimate();
  em3.estimate();

  return 0;
}