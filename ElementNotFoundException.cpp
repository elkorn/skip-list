#include <exception>
#include <sstream>
using namespace std;

template<typename Key>
class ElementNotFoundException: public exception {
    public:
        ElementNotFoundException(const Key& theKey): key(theKey) { }
        virtual ~ElementNotFoundException() throw() {}
        virtual const char* what() const throw() {
            stringstream result;
            result << "Key '" << key << "' does not exist in the set.";
            return result.str().c_str();
        }

    private:
            const Key &key;
};
