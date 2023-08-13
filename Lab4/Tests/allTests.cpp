#include "allTests.h"
#include "../Controller/FruitController.h"
#include <cassert>
#include <exception>
#include <iostream>


using std::exception, std::cout, std::endl;


void testDomain() {
    cout << "Domain test" << endl;

    Fruit fruit("banana", "Bolivia", {1, 1, 2023}, 10, 1.5);
    Date date = fruit.getExpDate();

    assert(fruit.getName() == "banana");
    assert(fruit.getOrigin() == "Bolivia");
    assert(date.day == 1 && date.month == 1 && date.year == 2023);
    assert(fruit.getPrice() == 1.5);
    assert(fruit.getQuantity() == 10);

    fruit.setPrice(10);
    assert(fruit.getPrice() == 10);
    fruit.setQuantity(10);
    assert(fruit.getQuantity() == 10);

    try {
        fruit.setQuantity(-10);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
    try {
        fruit.setPrice(-10);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }
}


void testRepo() {
    cout << "Repository test" << endl;

    Repository repo;
    assert(repo.getAll().size() == 10);

    Fruit banana("banana", "Bolivia", {1, 1, 2023}, 10, 1.5);

    repo.addFruit(banana);
    assert(repo.getAll().size() == 11);

    repo.addFruit(banana);
    assert(repo.getAll().back().getQuantity() == 20);

    repo.deleteFruit(banana);
    assert(repo.getAll().size() == 10);
}


void testController() {
    cout << "Controller test" << endl;

    Repository repo;
    Controller ctr(repo);

    assert(ctr.getAll().size() == 10);
    ctr.addFruit("pear", "Paraguay", {1, 1, 2023}, 10, 1.5);
    assert(ctr.getAll().size() == 11);

    try {
        ctr.addFruit("", "Bolivia", {1, 1, 2023}, -10, 1.5);
        assert(false);
    } catch (exception &e) {
        assert(true);
    }

    assert(ctr.deleteFruit("pear", "Paraguay") == true);
    assert(ctr.getAll().size() == 10);
    assert(ctr.deleteFruit("apple", "Thailand") == false);
    assert(ctr.getAll().size() == 10);
    assert(ctr.deleteFruit("kiwi", "Romania") == false);
    assert(ctr.getAll().size() == 10);

    assert(ctr.find("Australia").empty());
    assert(ctr.find("Romania").size() == 3);
    assert(ctr.find("rOManIa").size() == 3);
}


void testAll() {
    testDomain();
    testRepo();
    testController();
}
