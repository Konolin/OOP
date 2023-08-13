#include "L2_Mandru_Catalin_Problem2_duration.h"

// constructor
Duration::Duration(double value, char unit) {
    unit = tolower(unit);
    if (unit == UNIT_S || unit == UNIT_M || unit == UNIT_H) {
        this->unit = unit;
        this->value = value;
    }
}

// getter for value
double Duration::get_value() const { return value; }

// getter for unit
char Duration::get_unit() const { return unit; }

Duration Duration::add(const Duration &addedDuration) const {
    Duration temp = addedDuration.convert(unit);
    return {value + temp.value, unit};
}

Duration Duration::subtract(const Duration &subbedDuration) const {
    // check if the objects are measured in the same unit and makes sure the resulting object is not negative
    if (unit == subbedDuration.get_unit() && value >= subbedDuration.value)
        // returns new object with the difference of the two
        return {value - subbedDuration.value, unit};
    throw std::exception();
}

Duration Duration::scale(double scaleNr) const {
    // returns a new object scaled by a number
    return {value * scaleNr, unit};
}

Duration Duration::divide(double divideNr) const {
    // returns a new object divided by a number
    return {value / divideNr, unit};
}

std::string Duration::text() const {
    std::string valueString = std::to_string(value);
    int dotPosition = valueString.find('.');

    // only keep 2 digits after '.'
    if (dotPosition != -1)
        valueString = valueString.substr(0, dotPosition + 3);

    return valueString + " " + unit;
}

int Duration::compare(const Duration &compDuration) const {
    // comparison if the two obj have the same unit
    if (unit == compDuration.unit && value == compDuration.value) return 0;
    if (unit == compDuration.unit && value < compDuration.value) return -1;
    if (unit == compDuration.unit && value > compDuration.value) return 1;

    // the object with the larger unit wins
    if (unit == UNIT_H) return 1;
    if (compDuration.unit == UNIT_H) return -1;

    if (unit == UNIT_M && compDuration.unit == UNIT_S) return 1;
    // the last case: unit == "sec" && compDuration.unit == "min" => -1
    return -1;
}

Duration Duration::convert(const char conversionUnit) const {
    double newValue;

    if (unit == conversionUnit) newValue = value;

    if (unit == UNIT_H && conversionUnit == UNIT_M) newValue = value * 60;
    if (unit == UNIT_H && conversionUnit == UNIT_S) newValue = value * 3600;

    if (unit == UNIT_M && conversionUnit == UNIT_H) newValue = value / 60;
    if (unit == UNIT_M && conversionUnit == UNIT_S) newValue = value * 60;

    if (unit == UNIT_S && conversionUnit == UNIT_H) newValue = value / 3600;
    if (unit == UNIT_S && conversionUnit == UNIT_M) newValue = value / 60;

    return {newValue, conversionUnit};
}

// makes obj3 = obj1 + obj2 possible
Duration Duration::operator+(const Duration &addedDuration) const {
    if (unit == addedDuration.unit)
        return {value + addedDuration.value, unit};
    throw std::exception();
}

// makes obj3 = obj1 - obj2 possible
Duration Duration::operator-(const Duration &subbedDuration) const {
    if (unit == subbedDuration.unit && value >= subbedDuration.value)
        return {value - subbedDuration.value, unit};
    throw std::exception();
}

// makes obj2 = obj1 * nr possible
Duration Duration::operator*(double scaleNr) const {
    return {value * scaleNr, unit};
}

// makes obj2 = obj1 / nr possible
Duration Duration::operator/(double divideNr) const {
    return {value / divideNr, unit};
}
