#include <iostream>
#include <time.h>
#include <cstdlib>

int main()
{
  std::srand(time(0));
  const int nrolls=10000;  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute
  const int nintervals=10; // number of intervals

  int p[nintervals]={};

  for (int i=0; i<nrolls; ++i) {
    ++p[int(std::rand() % nintervals)];
  }

  std::cout << "uniform distribution: " << std::endl;
  std::cout << std::fixed; std::cout.precision(1);

  for (int i=0; i<nintervals; ++i) {
    std::cout << float(i)/nintervals << "-" << float(i+1)/nintervals << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }

  return 0;
}
