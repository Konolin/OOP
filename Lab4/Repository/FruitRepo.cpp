#include <stdexcept>
#include "FruitRepo.h"


Repository::Repository() {
    dummyData();
}


void Repository::addFruit(const Fruit &addedFruit) {
    // check if fruit already exists => increase quantity
    for (Fruit &fruit: fruitVector)
        if (fruit.getName() == addedFruit.getName() && fruit.getOrigin() == addedFruit.getOrigin()) {
            fruit.setQuantity(fruit.getQuantity() + addedFruit.getQuantity());
            return;
        }

    fruitVector.push_back(addedFruit);
}


void Repository::deleteFruit(const Fruit &deletedFruit) {
    for (auto it = fruitVector.begin(); it != fruitVector.end(); it++)
        if (it->getName() == deletedFruit.getName() && it->getOrigin() == deletedFruit.getOrigin()) {
            fruitVector.erase(it);
            return;
        }
}


vector<Fruit> Repository::getAll() { return fruitVector; }


void Repository::dummyData() {
    fruitVector.push_back(Fruit("apple", "Romania", {1, 12, 2024}, 150, 2));
    fruitVector.push_back(Fruit("pear", "Romania", {14, 9, 2023}, 100, 2.4));
    fruitVector.push_back(Fruit("banana", "Ecuador", {4, 5, 2023}, 98, 3.1));
    fruitVector.push_back(Fruit("grape", "Italy", {21, 9, 2023}, 239, 2.7));
    fruitVector.push_back(Fruit("apple", "Ukraine", {1, 11, 2024}, 90, 2.2));
    fruitVector.push_back(Fruit("plum", "Hungary", {28, 5, 2023}, 49, 3));
    fruitVector.push_back(Fruit("peach", "China", {5, 5, 2023}, 24, 3.8));
    fruitVector.push_back(Fruit("watermelon", "Bulgaria", {8, 8, 2023}, 37, 12));
    fruitVector.push_back(Fruit("cherry", "Romania", {12, 8, 2023}, 350, 1.2));
    fruitVector.push_back(Fruit("kiwi", "China", {14, 11, 2023}, 76, 4.4));
}
