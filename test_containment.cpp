#include <iostream>
#include "SkipList.cpp"
#include <ctime>
#include <fstream>
using namespace std;

int main()
{
  srand(time(0));
  const int nrolls=1000;  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute
  const int nintervals=32; // number of intervals
  const double lambda = 3.5;
  SkipList<int, int> *sl = new SkipList<int, int>();
    ofstream of;
    of.open("results.csv");

  for(int i = 0; i < nrolls; ++i) {
      sl->insert(i, i);
  }

  cout << "Done inserting." << endl;

  SkipList<int, int>::iterator begin = sl->begin();

  int p[nintervals]={};
  SkipListNode<int, int> *node, *endNode = (sl->end()->prev[0]->next[0]);
  for (int i=nintervals-1; i>=0; --i) {
    // if(i == 19) continue;
    node = begin->next[i];
    cout << "At level "<< i << endl;
    while(node != 0 && node != endNode) {
        ++p[i];
        node = node->next[i];
    }
  }

  cout << "containment (" << nrolls << " elements, * ~ around 10 elements):" << endl;
  cout << fixed; cout.precision(1);

  for (int i=0; i<nintervals; ++i) {
    cout << i << ": ";
    cout << string(p[i]*nstars/nrolls,'*') << endl;
  }

  delete sl;
  return 0;
}
