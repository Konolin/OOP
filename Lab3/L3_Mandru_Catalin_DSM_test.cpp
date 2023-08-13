#include "L3_Mandru_Catalin_DSM.h"
#include <string>
#include <cassert>
#include <iostream>
#include <exception>

using std::string, std::exception;

void basicTest() {
    // basic constructor
    DSM dsmElem(7);
    assert(dsmElem.size() == 0);

    // string array constructor
    string names[3] = {"unu", "doi", "trei"};
    DSM dsmNames(names, 3);
    assert(dsmNames.size() == 3);

    // add link (existing name)
    dsmNames.addLink("unu", "doi", 10);
    assert(dsmNames.size() == 3);

    // add link (new name)
    dsmNames.addLink("patru", "trei", 5);
    assert(dsmNames.size() == 4);

    // get name
    assert("patru" == dsmNames.getName(3));
    try {
        string invalid = dsmNames.getName(5);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    // set element
    dsmNames.setElementName(3, "replace");
    assert("replace" == dsmNames.getName(3));
    try {
        dsmNames.setElementName(5, "replace");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    // delete link
    try {
        dsmNames.deleteLink("zece", "unu");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    // has link
    dsmNames.addLink("unu", "doi", 10);
    assert(dsmNames.hasLink("unu", "doi"));
    dsmNames.deleteLink("doi", "trei");
    assert(dsmNames.hasLink("doi", "trei") == false);
    try {
        dsmNames.hasLink("zece", "unu");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    // count to links
    assert(dsmNames.countToLinks("unu") == 1);
    try {
        assert(dsmNames.countToLinks("boga") == 1);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    // count from links
    assert(dsmNames.countFromLinks("doi") == 1);
    try {
        assert(dsmNames.countFromLinks("comi") == 1);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    // count all links
    assert(dsmNames.countAllLinks() == 2);

    std::cout << "Basic tests done!\n";
}

void bonusPunkTest() {
    // load from file
    try {
        DSM dsm = DSM::loadFromFile("invalid.csv");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    DSM dsmExpected(4);
    dsmExpected.addLink("unu", "trei", 1);
    dsmExpected.addLink("patru", "doi", 13);
    dsmExpected.addLink("unu", "doi", 30);
    dsmExpected.addLink("doi", "trei", 1);
    dsmExpected.addLink("trei", "doi", 20);

    DSM dsm = DSM::loadFromFile("input.csv");
    assert(dsm == dsmExpected);

    dsm.storeToFile("output.csv");

    std::cout << "Bonuspunkt test done!\n";
}

int main() {
    basicTest();
    bonusPunkTest();

    std::cout << "Tests done\n";

    return 0;
}
