#include <string.h>
#include <iostream>
#include <utility>
#include <time.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <set>
#include <list>
#include <vector>
#include <iterator>
#include <sstream>

using namespace std;
float sec(clock_t time)
{
    return (float)time / CLOCKS_PER_SEC;
}

vector<string> readData(const char* path)
{
    const vector<string> dest();
        ifstream input(path);
    stringstream str;
    copy(istreambuf_iterator<char>(input),
        istreambuf_iterator<char>(),
        ostreambuf_iterator<char>(str));
    return vector<string>(istream_iterator<string>(str), istream_iterator<string>());
}

using namespace std;
int main(int argc, char **argv)
{
    srand(time(0));
    std::stringstream dir;
    dir << "results/";
    if (argc > 1)
    {
        dir << std::string(argv[1]) << "/";
    }

    ofstream inserting, erasing, finding, elements;
    elements.open(dir.str() + "string_elements.csv");
    inserting.open(dir.str() + "string_inserting.csv");
    finding.open(dir.str() + "string_finding.csv");
    erasing.open(dir.str() + "string_erasing.csv");

    clock_t start, t, total;
    std::vector<string> values = readData("lab1.dic");
    int MAX = values.size();
    const int INCREMENT = 1000;

    std::random_shuffle(values.begin(), values.end());

    total = clock();
    for (int LIMIT = INCREMENT; LIMIT < MAX; LIMIT += INCREMENT)
    {
        cout << "Procesing " << LIMIT << " elements..." << endl;
        set<string> theList = set<string> ();
        elements << LIMIT << endl;

        cout << "\tInsert" << endl;
        t = 0;
        for (int i = 0; i < LIMIT; ++i)
        {
            start = clock();
            theList.insert(values[i]);
            t += clock() - start;
        }

        inserting << sec(t) << endl;

        cout << "\tFind" << endl;
        t = 0;
        for (int i = 0; i < LIMIT; ++i)
        {
            start = clock();
            theList.find(values[i]);
            t += clock() - start;
        }

        finding << sec(t) << endl;

        cout << "\tErase" << endl;
        t = 0;
        for (int i = 0; i < LIMIT; ++i)
        {
            set<string>::iterator it = theList.begin();
            start = clock();
            theList.erase(it);
            t += clock() - start;
        }

        erasing << sec(t) << endl;
    }

    total = clock() - total;
    cout << "Total: " << sec(total) << " seconds." << endl;

    inserting.close();
    elements.close();
    finding.close();
    erasing.close();
    return 0;
}
