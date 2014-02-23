#include <iostream>
#include <random>
#include "ExponentialRandomHeight.cpp"

int main()
{
  const int nrolls=10000000;  // number of experiments
  const int nstars=1000;    // maximum number of stars to distribute
  const int nintervals=32; // number of intervals
  const double lambda = 3.5;

  ExponentialRandomHeight randomizer(nintervals, lambda);

  int p[nintervals]={};

  for (int i=0; i<nrolls; ++i) {
    ++p[randomizer.newLevel()];
  }

  std::cout << "randomizer (" << lambda << "):" << std::endl;
  std::cout << std::fixed; std::cout.precision(1);

  for (int i=0; i<nintervals; ++i) {
    std::cout << i << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }

  return 0;
}
