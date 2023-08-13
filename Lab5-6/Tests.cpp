#include "Tests.h"
#include "Scooter.h"
#include "InMemoryRepository.h"
#include "CSVFileRepository.h"
#include <iostream>
#include <cassert>


using Test::Tests, std::cout, Domain::Scooter, std::exception, Repository::InMemoryRepository, Repository::CSVRepository;


void Tests::Tests::testAll() {
    cout << "Starting all tests...\n\n";

    testDomain();
    testInMemoryRepository();
    testCSVRepository();
    testController();

    cout << "All tests done!\n\n\n";
}


void Tests::testDomain() {
    cout << "Starting domain test...\n";

    Scooter scooter("IDK", "Mercedes", {1, 1, 2023}, 531,
                    "Str. Academician David Prodan nr. 7", Domain::parked);

    // test getters
    assert(scooter.getId() == "IDK");
    assert(scooter.getModel() == "Mercedes");
    Domain::Date commissionDate = scooter.getCommissionDate();
    assert(commissionDate.day == 1);
    assert(commissionDate.month == 1);
    assert(commissionDate.year == 2023);
    assert(scooter.getMileage() == 531);
    assert(scooter.getLastLocation() == "Str. Academician David Prodan nr. 7");
    assert(scooter.getStatus() == Domain::parked);

    // test setters: valid data
    scooter.setId("yad");
    assert(scooter.getId() == "yad");
    scooter.setModel("BMW");
    assert(scooter.getModel() == "BMW");
    scooter.setCommissionDate({2, 2, 2022});
    commissionDate = scooter.getCommissionDate();
    assert(commissionDate.day == 2);
    assert(commissionDate.month == 2);
    assert(commissionDate.year == 2022);
    scooter.setMileage(420);
    assert(scooter.getMileage() == 420);
    scooter.setLastLocation("GROAPAAA");
    assert(scooter.getLastLocation() == "GROAPAAA");
    scooter.setStatus(Domain::inUse);
    assert(scooter.getStatus() == Domain::inUse);

    // test setters: invalid data
    try {
        scooter.setId("1qw");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    try {
        scooter.setModel("");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    try {
        scooter.setCommissionDate({30, 2, 2023});
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    try {
        scooter.setMileage(-129);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    try {
        scooter.setLastLocation("");
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    cout << "Domain test done!\n\n";
}


void Tests::testInMemoryRepository() {
    cout << "Starting in memory repository test...\n";

    // check the original size of the vector from the array
    InMemoryRepository repository;
    assert(repository.getAll().size() == 10);

    // check the add method
    Scooter scooter("IFW", "MyriaMM", {1, 1, 2022}, 931, "Centru", Domain::inUse);
    repository.add(scooter);
    assert(repository.getAll().size() == 11);
    assert(repository.getAll().back() == scooter);

    // check the getById method
    string id = scooter.getId();
    assert(repository.getById(id) == scooter);

    // check the remove method
    repository.remove(scooter);
    assert(repository.getAll().size() == 10);

    // check update method
    try {
        repository.update(scooter);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    repository.add(scooter);
    scooter.setMileage(999);
    repository.update(scooter);
    assert(repository.getById("IFW").getMileage() == 999);

    cout << "Repository in memory test done!\n\n";
}


void Tests::testCSVRepository() {
    cout << "Starting CSV repository test...\n";

    // check the original size of the vector from the array
    CSVRepository repository;
    int originalSize = repository.getAll().size();
    assert(repository.getAll().size() == originalSize);

    // check the add method
    Scooter scooter("IFW", "MyriaMM", {1, 1, 2022}, 931, "Centru", Domain::inUse);
    repository.add(scooter);
    assert(repository.getAll().size() == originalSize + 1);
    assert(repository.getAll().back() == scooter);

    // check the getById method
    string id = scooter.getId();
    assert(repository.getById(id) == scooter);

    // check the remove method
    repository.remove(scooter);
    assert(repository.getAll().size() == originalSize);

    // check update method
    try {
        repository.update(scooter);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    repository.add(scooter);
    scooter.setMileage(999);
    repository.update(scooter);
    assert(repository.getById("IFW").getMileage() == 999);

    repository.remove(scooter);

    cout << "Repository CSV test done!\n\n";
}


void Tests::testController() {
    cout << "Starting controller test...\n";

    cout << "Controller test done!\n\n";
}
