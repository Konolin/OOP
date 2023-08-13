#include <string>

class Duration {
private:
    double value;
    char unit;

public:
    static const char UNIT_S = 's';
    static const char UNIT_H = 'h';
    static const char UNIT_M = 'm';

    // constructor
    Duration(double value, char unit);

    // getter for value
    double get_value() const;

    // getter for unit
    char get_unit() const;

    // addition of two objects, returns another object
    Duration add(const Duration &addedDuration) const;

    // subtraction of two objects, returns another object
    Duration subtract(const Duration &subbedDuration) const;

    // scales an objects value by a number
    Duration scale(double scaleNr) const;

    // divides an objects value by a number
    Duration divide(double divideNr) const;

    // returns a string from the object
    std::string text() const;

    // compares 2 objects, -1 obj1 < obj2; 0 => obj1 == obj2; 1 => obj1 > obj2
    int compare(const Duration &compDuration) const;

    // converts an objects unit (h -> min, h -> sec, etc.)
    Duration convert(char conversionUnit) const;

    // makes obj3 = obj1 + obj2 possible
    Duration operator+(const Duration &addedDuration) const;

    // makes obj3 = obj1 - obj2 possible
    Duration operator-(const Duration &subbedDuration) const;

    // makes obj2 = obj1 * nr possible
    Duration operator*(double scaleN) const;

    // makes obj2 = obj1 / nr possible
    Duration operator/(double divideNr) const;
};

