#pragma once

#include "../Repository/FruitRepo.h"

class Controller {
private:
    Repository fruitRepo;

    static void dataCheck(const string &name, const string &origin, const Date &expDate, int quantity, float price);

public:
    Controller(Repository fruitRepo);

    static string stringToLower(string input);

    void addFruit(const string &_name, const string &_origin, Date _expDate, int _quantity, float _price);

    bool deleteFruit(const string &deleteName, const string &deleteOrigin);

    vector<Fruit> runningLow(int minQuantity);

    vector<Fruit> find(string origin);

    static bool compareFruitExpDate(const Fruit &fruit1, const Fruit &fruit2);

    vector<Fruit> getAll();
};
