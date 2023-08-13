#include "L2_Mandru_Catalin_Problem2_duration.h"
#include <iostream>
#include <cassert>
#include <string>

void testAll() {
    Duration duration1(100, Duration::UNIT_M);

    // test get/set methods
    assert(duration1.get_value() == 100);
    assert(duration1.get_unit() == Duration::UNIT_M);

    Duration duration2(10.5, Duration::UNIT_M);
    Duration duration3(1, Duration::UNIT_H);
    Duration addDuration1 = duration1.add(duration2);
    Duration addDuration2 = duration1.add(duration3);
    Duration subDuration = duration1.subtract(duration2);

    // test add method
    assert(addDuration1.get_value() == 110.5);
    assert(addDuration2.get_value() == 160);

    // test subtraction method
    assert(subDuration.get_value() == 89.5);
    try {
        duration1.subtract(duration3);
        assert(false);
    }
    catch (std::exception&) {
        assert(true);
    }

    // test scale method
    Duration scaledDuration = duration1.scale(2.5);
    assert(scaledDuration.get_value() == 250);

    // test divide method
    Duration divideDuration = duration1.divide(4);
    assert(divideDuration.get_value() == 25);

    // test text method
    assert(duration1.text() == "100.00 m");

    // test compare method
    assert(duration1.compare(duration1) == 0);
    assert(duration1.compare(duration2) == 1);
    assert(duration1.compare(duration3) == -1);

    // test convert method
    Duration convertedDuration1 = duration1.convert(Duration::UNIT_S);
    assert(convertedDuration1.get_value() == 6000);
    assert(convertedDuration1.get_unit() == Duration::UNIT_S);

    // test operator methods
    // addition operator
    Duration expectedDurationAdd = Duration(110.5, Duration::UNIT_M);
    assert(expectedDurationAdd.compare(duration1 + duration2) == 0);

    // substitution operator
    Duration expectedDurationSub = Duration(89.5, Duration::UNIT_M);
    assert(expectedDurationSub.compare(duration1 - duration2) == 0);

    // multiplication (scale) operator
    Duration expectedDurationScale = Duration(200, Duration::UNIT_M);
    assert(expectedDurationScale.compare(duration1 * 2) == 0);

    // division operator
    Duration expectedDurationDivide = Duration(50, Duration::UNIT_M);
    assert(expectedDurationDivide.compare(duration1 / 2) == 0);

    std::cout << "All tests done!" << std::endl;
}

void userTest() {
    double value1, value2, scale;
    char unit1, unit2;

    // get the values for the first object
    std::cout << "Enter the first value (double): ";
    std::cin >> value1;
    std::cout << "Enter the first unit (s/m/h): ";
    std::cin >> unit1;

    // get the values for the second object
    std::cout << "Enter the second value (double): ";
    std::cin >> value2;
    std::cout << "Enter the second unit (s/m/h): ";
    std::cin >> unit2;

    std::cout << "Enter a number (for scaling/dividing): ";
    std::cin >> scale;

    // create the two objects
    Duration duration1 = Duration(value1, unit1);
    Duration duration2 = Duration(value2, unit2);

    // make sure they have the same unit
    duration2 = duration2.convert(duration1.get_unit());

    // display addition
    Duration sum = duration1.add(duration2);
    std::cout << "Addition: " << sum.text() << std::endl;

    // display subtraction
    try {
        Duration sub = duration1.subtract(duration2);
        std::cout << "Subtraction: " << sub.text() << std::endl;
    } catch (std::exception &) {
        std::cerr << "Subtraction error: Value 1 < Value 2 !";
    }

    // display comparison
    std::cout << "Compare duration1, duration2: " << duration1.compare(duration2) << std::endl;

    // display scaling
    duration1 = duration1.scale(scale);
    std::cout << "Duration1 scaled: " << duration1.text() << std::endl;

    // display division
    duration2 = duration2.divide(scale);
    std::cout << "Duration1 divided: " << duration2.text() << std::endl;
}


int main() {
    testAll();
    userTest();

    return 0;
}