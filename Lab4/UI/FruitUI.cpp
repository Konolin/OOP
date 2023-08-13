#include "FruitUI.h"
#include "../Tests/allTests.h"
#include <iostream>
#include <utility>


using std::cout, std::cin, std::to_string;


UI::UI(Controller controller) : fruitController(std::move(controller)) {}


void UI::mainMenuUI() {
    cout << "~~~~~ Main menu: ~~~~~\n\n";
    cout << "1. Add fruit\n";
    cout << "2. Remove fruit\n";
    cout << "3. Print fruit\n";
    cout << "4. Products that are running low\n";
    cout << "5. Print expiration dates\n";
    cout << "6. Run all tests\n";
    cout << "7. Exit\n\n";
    cout << "Choose an option: ";
}


void UI::mainMenu() {
    string optionStr;
    int optionInt;

    while (true) {
        cout << string(30, '\n');
        mainMenuUI();
        cin >> optionStr;
        cout << string(30, '\n');

        try {
            optionInt = std::stoi(optionStr);
        } catch (std::exception &e) {
            optionInt = -1;
        }

        switch (optionInt) {
            case 1:
                addFruit();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 2:
                deleteFruit();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 3:
                printFruit();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 4:
                runningLow();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 5:
                printExpirationDates();
                cin.ignore();
                cout << "\nPress any key to continue...";
                cin.get();
                continue;
            case 6:
                testAll();
                cout << "All tests completed\n\n";
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 7:
                break;
            default:
                cin.ignore();
                cout << "Invalid input, try again\n\n";
                cout << "Press any key to continue...";
                cin.get();
                continue;
        }
        break;
    }
}


void UI::addFruit() {
    string name{}, origin{};
    Date expDate{};
    int quantity{};
    float price{};

    cout << "Name: ";
    cin >> name;

    cout << "Origin: ";
    cin >> origin;

    cout << "Date:\n";
    cout << "\tDay: ";
    cin >> expDate.day;
    cout << "\tMonth: ";
    cin >> expDate.month;
    cout << "\tYear: ";
    cin >> expDate.year;

    cout << "Quantity: ";
    cin >> quantity;

    cout << "Price: ";
    cin >> price;

    cin.ignore();

    try {
        fruitController.addFruit(name, origin, expDate, quantity, price);
        cout << "\nFruit successfully added!\n\n";
    } catch (std::exception &e) {
        cout << "\nOne or more attributes are not valid, try again!\n\n";
    }
}


void UI::deleteFruit() {
    string name, origin;

    cout << "Name: ";
    cin >> name;
    cout << "Origin: ";
    cin >> origin;

    cin.ignore();

    if (fruitController.deleteFruit(name, origin))
        cout << "\nThe fruit successfully deleted!\n\n";
    else cout << "\nThe fruit does not exist in the inventory.\n\n";
}


void UI::printFruit() {
    string input;

    cin.ignore();
    cout << "Enter the name/origin: ";
    std::getline(cin, input);

    cout << "\n";
    bool successful = printSearchedFruit(input);
    cout << "\n";

    if (!successful) cout << "No fruit containing \"" << input << "\" was found.\n\n";
}


void UI::runningLow() {
    int minQuantity;

    cout << "Enter minimum quantity: ";
    cin >> minQuantity;
    cout << '\n';
    cin.ignore();

    vector<Fruit> fruitRunningLow = fruitController.runningLow(minQuantity);

    if (!fruitRunningLow.empty()) {
        printFruitVector(fruitRunningLow);
        cout << '\n';
    } else
        cout << "\nThere are no fruit with a quantity less then " << minQuantity << " in the inventory\n\n";
}


void UI::printFruitVector(vector<Fruit> fruitVector) {
    sort(fruitVector.begin(), fruitVector.end(),
         [](const Fruit &fruit1, const Fruit &fruit2) { return fruit1.getName() < fruit2.getName(); });

    int index = 1;
    for (Fruit &fruit: fruitVector) printFruit(fruit, index++);
}


void UI::printFruit(Fruit &fruit, int index) {
    cout << index << ". " << "Name: " << fruit.getName() << ", Origin: " << fruit.getOrigin() << ", Date: "
         << expDateToString(fruit.getExpDate()) << ", Quantity: " << fruit.getQuantity() << ", Price: "
         << fruit.getQuantity() << '\n';
}


string UI::expDateToString(const Date &expDate) {
    return to_string(expDate.day) + ':' + to_string(expDate.month) + ':' + to_string(expDate.year);
}


void UI::printExpirationDates() {
    auto fruitVector = fruitController.getAll();

    sort(fruitVector.begin(), fruitVector.end(), Controller::compareFruitExpDate);

    int index = 1;
    for (Fruit &fruit: fruitVector) printFruit(fruit, index++);
}


bool UI::printSearchedFruit(string searchedString) {
    searchedString = Controller::stringToLower(searchedString);
    string currentName, currentOrigin;
    vector<Fruit> fruitVector;

    for (const Fruit &fruit: fruitController.getAll()) {
        currentName = Controller::stringToLower(fruit.getName());
        currentOrigin = Controller::stringToLower(fruit.getOrigin());

        if (searchedString.empty() || currentName.find(searchedString) != string::npos ||
            currentOrigin.find(searchedString) != string::npos)
            fruitVector.push_back(fruit);
    }

    if (!fruitVector.empty()) {
        printFruitVector(fruitVector);
        return true;
    } else return false;
}