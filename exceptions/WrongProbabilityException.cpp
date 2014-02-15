#include <exception>
#include <sstream>

class WrongProbabilityException: public std::exception {
    public:
        WrongProbabilityException(const float theProbability): probability(theProbability) { }
        virtual ~WrongProbabilityException() throw() {}
        virtual const char* what() const throw() {
            std::stringstream result;
            result << "Probability value '" << probability << "' should belong to [0-1].";
            return result.str().c_str();
        }

    private:
            const float probability;
};
