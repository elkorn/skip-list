#include <exception>
#include <sstream>

template<typename Key>
class ElementNotFoundException: public std::exception {
    public:
        ElementNotFoundException(const Key& theKey): key(theKey) { }
        virtual ~ElementNotFoundException() throw() {}
        virtual const char* what() const throw() {
            std::stringstream result;
            result << "Key '" << key << "' does not exist in the set.";
            return result.str().c_str();
        }

    private:
            const Key &key;
};
