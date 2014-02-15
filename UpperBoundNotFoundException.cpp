#include <exception>
#include <sstream>
using namespace std;

template<typename Key>
class UpperBoundNotFoundException: public exception {
    public:
        UpperBoundNotFoundException(const Key& theKey): key(theKey) { }
        virtual ~UpperBoundNotFoundException() throw() {}
        virtual const char* what() const throw() {
            stringstream result;
            result << "An upper bound for key '" << key << "' does not exist in the set.";
            return result.str().c_str();
        }

    private:
            const Key &key;
};
