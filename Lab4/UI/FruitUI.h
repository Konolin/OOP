#pragma once

#include "../Controller/FruitController.h"

class UI {
private:
    Controller fruitController;

    static void mainMenuUI();

    void addFruit();

    void deleteFruit();

    void printFruit();

    void runningLow();

    static void printFruitVector(vector<Fruit> fruitVector);

    static void printFruit(Fruit &fruit, int index);

    static string expDateToString(const Date &expDate);

    void printExpirationDates();

    bool printSearchedFruit(string searchedString);

public:
    UI(Controller fruitController);

    void mainMenu();
};