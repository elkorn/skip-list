#include <exception>
#include <sstream>
using namespace std;

template<typename Key>
class LowerBoundNotFoundException: public exception {
    public:
        LowerBoundNotFoundException(const Key& theKey): key(theKey) { }
        virtual ~LowerBoundNotFoundException() throw() {}
        virtual const char* what() const throw() {
            stringstream result;
            result << "A lower bound for key '" << key << "' does not exist in the set.";
            return result.str().c_str();
        }

    private:
            const Key &key;
};
