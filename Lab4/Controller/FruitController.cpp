#include "FruitController.h"
#include <stdexcept>
#include <utility>


Controller::Controller(Repository fruitRepo) : fruitRepo(std::move(fruitRepo)) {}


void Controller::addFruit(const string &name, const string &origin, Date expDate, int quantity, float price) {
    dataCheck(name, origin, expDate, quantity, price);
    Fruit addedFruit(name, origin, expDate, quantity, price);
    fruitRepo.addFruit(addedFruit);
}


bool Controller::deleteFruit(const string &deleteName, const string &deleteOrigin) {
    string deleteNameLower, deleteOriginLower, nameLower;
    deleteNameLower = stringToLower(deleteName);
    vector<Fruit> matchingFruit = find(deleteOrigin);

    if (!matchingFruit.empty())
        for (const Fruit &fruit: matchingFruit) {
            nameLower = stringToLower(fruit.getName());

            if (nameLower == deleteNameLower) {
                fruitRepo.deleteFruit(fruit);
                return true;
            }
        }
    return false;
}


vector<Fruit> Controller::find(string origin) {
    vector<Fruit> foundFruits;
    string currentOrigin;
    origin = stringToLower(origin);

    for (const Fruit &fruit: fruitRepo.getAll()) {
        currentOrigin = stringToLower(fruit.getOrigin());

        if (currentOrigin == origin)
            foundFruits.push_back(fruit);
    }
    return foundFruits;
}


vector<Fruit> Controller::runningLow(int minQuantity) {
    vector<Fruit> fruitVector;

    for (const Fruit &fruit: fruitRepo.getAll())
        if (fruit.getQuantity() <= minQuantity) fruitVector.push_back(fruit);

    return fruitVector;
}


string Controller::stringToLower(string input) {
    for (char &c: input) c = tolower(c);
    return input;
}


bool Controller::compareFruitExpDate(const Fruit &fruit1, const Fruit &fruit2) {
    if (fruit1.getExpDate().year != fruit2.getExpDate().year)
        return fruit1.getExpDate().year < fruit2.getExpDate().year;

    if (fruit1.getExpDate().month != fruit2.getExpDate().month)
        return fruit1.getExpDate().month < fruit2.getExpDate().month;

    return fruit1.getExpDate().day < fruit2.getExpDate().day;
}


void Controller::dataCheck(const string &name, const string &origin, const Date &expDate, int quantity, float price) {
    if (name.empty() || origin.empty())
        throw std::invalid_argument("Name or origin is not valid.");

    if (expDate.day < 1 || expDate.day > 31)
        throw std::invalid_argument("Expiration date day is not valid.");

    if (expDate.day == 31 && expDate.month % 2 == 0)
        throw std::invalid_argument("Expiration date day is not valid.");

    if (expDate.day > 28 && expDate.month == 2 && expDate.year % 4 != 0)
        throw std::invalid_argument("Expiration date day is not valid.");

    if (expDate.day > 29 && expDate.month == 2 && expDate.year % 4 == 0)
        throw std::invalid_argument("Expiration date day is not valid.");

    if (expDate.month < 1 || expDate.month > 12)
        throw std::invalid_argument("Expiration date month is not valid.");

    if (expDate.year < 2023)
        throw std::invalid_argument("Expiration date year is not valid.");

    if (quantity < 0)
        throw std::invalid_argument("Quantity is not valid.");

    if (price < 0)
        throw std::invalid_argument("Price is not valid.");
}


vector<Fruit> Controller::getAll() {
    return fruitRepo.getAll();
}
