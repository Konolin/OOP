#include "UI.h"
#include "User.h"
#include "CSVFileRepository.h"
#include <iostream>
#include <utility>


using UserInterface::UI, std::cout, std::cin, std::to_string, Domain::User, Domain::inUse, Domain::inMaintenance,
        Domain::parked, Domain::reserved, Domain::outOfService, std::exception, Domain::User;


UI::UI(shared_ptr<Ctr> _controller) : controller(std::move(_controller)) {}


void UI::startUI() {
    cout << string(30, '\n');

    selectRepoType();

    userCredentialsInput();
    if (user.getName() == "owner") {
        ownerMenu();
    } else {
        customerMenu();
    }
}


void UI::selectRepoType() {
    string repoType;
    cout << "Select the repository type (memo / csv): ";
    cin >> repoType;

    if (repoType == "csv") {
        shared_ptr<IRepository> repo = std::make_shared<Repository::CSVRepository>();
        controller = std::make_shared<Ctr>(repo);
    } else if (repoType != "memo") {
        cin.ignore();
        cout << "Invalid input, try again.\n";
        cout << "Press any key to continue...";
        cin.get();
        selectRepoType();
    }
}

void UI::userCredentialsInput() {
    string userType, userPassword;

    cout << "Select a role (owner / customer): ";
    cin >> userType;
    cout << "Enter the password (s8cr8t / tr1ck) ~de test~ : ";
    cin >> userPassword;

    if (userType == "owner" && userPassword == "s8cr8t" || userType == "customer" && userPassword == "tr1ck") {
        user.setName(userType);
        user.setPassword(userPassword);
    } else {
        cin.ignore();
        cout << "Invalid input, or user type + password, try again.\n";
        cout << "Press any key to continue...";
        cin.get();
        userCredentialsInput();
    }
}


void UI::ownerMenuUI() {
    cout << "~~~~~ Main menu: ~~~~~\n\n";
    cout << "1. Add scooter\n";
    cout << "2. Delete scooter\n";
    cout << "3. Edit scooter\n";
    cout << "4. Search scooter by location\n";
    cout << "5. Filter scooters by age or mileage\n";
    cout << "6. View all scooters\n";
    cout << "7. Return to user choice\n";
    cout << "8. Exit\n\n";
    cout << "Choose an option: ";
}


void UI::ownerMenu() {
    string optionStr;
    int optionInt;

    while (true) {
        cout << string(30, '\n');
        ownerMenuUI();
        cin >> optionStr;
        cout << string(30, '\n');

        try {
            optionInt = stoi(optionStr);
        } catch (exception &e) {
            optionInt = -1;
        }

        switch (optionInt) {
            case 1:
                addScooter();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 2:
                deleteScooter();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 3:
                editScooter();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 4:
                searchByLocation();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 5:
                filterScooters();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 6:
                viewScooters();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 7:
                startUI();
            case 8:
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


void UI::customerMenuUI() {
    cout << "~~~~~ Main menu: ~~~~~\n\n";
    cout << "1. Search scooter by location\n";
    cout << "2. Filter scooters scooters\n";
    cout << "3. Reserve a scooter\n";
    cout << "4. See all reserved scooters\n";
    cout << "5. Use a scooter\n";
    cout << "6. See all your in use scooters\n";
    cout << "7. Park a scooter\n";
    cout << "8. Return to user choice\n";
    cout << "9. Exit\n\n";
    cout << "Choose an option: ";
}


void UI::customerMenu() {
    string optionStr;
    int optionInt;

    while (true) {
        cout << string(30, '\n');
        customerMenuUI();
        cin >> optionStr;
        cout << string(30, '\n');

        try {
            optionInt = stoi(optionStr);
        } catch (exception &e) {
            optionInt = -1;
        }

        switch (optionInt) {
            case 1:
                searchByLocation();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 2:
                filterScooters();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 3:
                reserveScooter();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 4:
                showAllReservedScooters();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 5:
                useScooter();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 6:
                showAllInUseScooter();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 7:
                parkScooter();
                cin.ignore();
                cout << "Press any key to continue...";
                cin.get();
                continue;
            case 8:
                startUI();
            case 9:
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


void UI::addScooter() {
    cout << "~~~~~  Adding a scooter  ~~~~~\n\n";

    string id, model, lastLocation, user_input;
    int year, month, day, mileage;
    Status status;

    cin.ignore();

    cout << "Type the ID of the new scooter (3 letters): ";
    getline(cin, id);

    cout << "Type the model of the new scooter: ";
    getline(cin, model);

    cout << "Type the commission date of the new scooter:\n";
    cout << "Day: ";
    getline(cin, user_input);
    day = stoi(user_input);
    cout << "Month: ";
    getline(cin, user_input);
    month = stoi(user_input);
    cout << "Year: ";
    getline(cin, user_input);
    year = stoi(user_input);

    cout << "Type the mileage of the new scooter: ";
    getline(cin, user_input);
    mileage = stoi(user_input);

    cout << "Type the last location of the new scooter: ";
    getline(cin, lastLocation);

    cout << "Type the status of the new scooter (parked, reserved, in use, in maintenance, out of service): ";
    getline(cin, user_input);

    if (user_input == "parked") {
        status = parked;
    } else if (user_input == "reserved") {
        status = reserved;
    } else if (user_input == "in use") {
        status = inUse;
    } else if (user_input == "in maintenance") {
        status = inMaintenance;
    } else if (user_input == "out of service") {
        status = outOfService;
    }

    if (controller->add(id, model, {day, month, year}, mileage, lastLocation, status)) {
        cout << "\nThe scooter has been added to the repository!\n\n";
    } else {
        cout << "\nFailed to add the scooter!\n\n";
    }
}


void UI::deleteScooter() {
    cout << "~~~~~  Removing a scooter  ~~~~~\n\n";

    string id;
    cout << "Type the id of the scooter to be removed: ";
    cin.ignore();
    getline(cin, id);

    if (controller->remove(id)) {
        cout << "\nThe scooter has been removed!\n\n";
    } else {
        cout << "\nNo scooter id matched your input!\n\n";
    }
}


void UI::editScooter() {
    cout << "~~~~~  Editing a scooter  ~~~~~\n\n";

    string id, newMileage, user_input, choice;

    cout << "Type the id of the scooter:";
    cin.ignore();
    getline(cin, id);
    Scooter scooter = controller->repository->getById(id);

    cout << "Here is the selected scooter:\n\n";
    cout << "Scooter ID: " << id << '\n';
    cout << "Model: " << scooter.getModel() << '\n';
    cout << "Commission Date: " << scooter.getCommissionDate().year << "/" <<
         scooter.getCommissionDate().month << "/" << scooter.getCommissionDate().day << '\n';
    cout << "Mileage: " << scooter.getMileage() << '\n';
    cout << "Last Location: " << scooter.getLastLocation() << '\n';
    cout << "Status: " << statusToString(scooter.getStatus()) << "\n\n";

    cout << "What would you like to edit to this scooter? (Mileage / Last Location / Status): ";
    getline(cin, choice);

    if (choice == "Mileage") {
        cout << "Enter the new mileage: ";
        getline(cin, user_input);

        if (controller->edit(id, "mileage", user_input)) {
            cout << "Mileage updated successfully\n!";
        } else {
            cout << "Failed to update the mileage!\n";
        }

    } else if (choice == "Last Location") {
        cout << "Enter the last location: ";
        getline(cin, user_input);

        if (controller->edit(id, "lastLocation", user_input)) {
            cout << "Last location updated successfully!\n";
        } else {
            cout << "Failed to update the last location!\n";
        }

    } else if (choice == "Status") {
        cout << "Enter the new status (parked, reserved, in use, in maintenance, out of service): ";
        getline(cin, user_input);

        if (controller->edit(id, "status", user_input)) {
            cout << "Status updated successfully!\n";
        } else {
            cout << "Failed to update the status!\n";
        }
    }
}


void UI::searchByLocation() {
    string location;
    cout << "~~~~ Search by location ~~~~\n\n";
    cout << "Enter the location you want to search scooters in: ";
    cin.ignore();
    getline(cin, location);
    cout << '\n';

    vector<Scooter> filteredVector = controller->searchByLocation(location);
    if (!filteredVector.empty()) {
        printScooterVector(filteredVector);
    } else {
        cout << "No scooter with specified location was found.\n";
    }
}


void UI::filterScooters() {
    int input, mileage;
    vector<Scooter> filteredVector;
    Date commissionDate{};

    cin.ignore();
    cout << "~~~~ Filter scooters ~~~~\n";
    cout << "Would you like to filter scooters by: \n\n1. Commission date\n2. Mileage\n\n";
    cout << "Choose an option: ";
    cin >> input;

    switch (input) {
        case 1:
            cout << "\nFilter all the scooters with the commission date before: \n\tDay: ";
            cin >> commissionDate.day;
            cout << "\tMonth: ";
            cin >> commissionDate.month;
            cout << "\tYear: ";
            cin >> commissionDate.year;
            filteredVector = controller->filterScooterDate(commissionDate);
            break;
        case 2:
            cout << "\nFilter all the scooters with the mileage under: ";
            cin >> mileage;
            filteredVector = controller->filterScooterMileage(mileage);
            break;
        default:
            cout << "Invalid input, try again...";
            cin.get();
            filterScooters();
    }

    printScooterVector(filteredVector);
}


void UI::viewScooters() {
    cout << string(30, '\n');
    cout << "~~~~ View scooters sorted by commission date ~~~~\n\n";

    vector<Scooter> sortedScooters = controller->sortedByCommissionDate();
    printScooterVector(sortedScooters);
}


void UI::reserveScooter() {
    cout << "~~~~ Available scooters ~~~~\n\n";
    vector<Scooter> availableScooters = controller->findAvailableScooters();

    if (!availableScooters.empty()) {
        printScooterVector(availableScooters);

        cout << "\n~~~~ Reserve a scooter ~~~~\n\n";

        string id;
        cin.ignore();
        cout << "Enter the id of the scooter you want to reserve: ";
        cin >> id;

        if (controller->reserveScooter(id)) {
            cout << "\nScooter successfully reserved\n\n";
            user.addReservedScooter(controller->repository->getById(id));
        } else {
            cout << "\nScooter could not be reserved.\n\n";
        }
    } else {
        cout << "No scooters are available at this moment.\n\n";
    }
}


void UI::useScooter() {
    cout << "~~~~ Available scooters ~~~~\n\n";
    vector<Scooter> availableScooters = controller->findAvailableScooters();

    if (!availableScooters.empty()) {
        printScooterVector(availableScooters);

        cout << "\n~~~~ Use a scooter ~~~~\n\n";
        string id;
        cin.ignore();
        cout << "Enter the id of the scooter you want to use: ";
        cin >> id;

        if (controller->useScooter(id)) {
            cout << "\nScooter is now successfully in use.\n\n";
            user.addInUseScooter(controller->repository->getById(id));
        } else {
            cout << "\nScooter can not be used right now.\n\n";
        }

    } else {
        cout << "No scooters are available at this moment.\n\n";
    }
}

void UI::showAllReservedScooters() {
    cout << "~~~~ Reserved scooters ~~~~\n";

    vector<Scooter> reservedScooters = user.getAllReservedScooters();
    if (!reservedScooters.empty()) {
        cout << "Here is a list of all reserved scooters:\n\n";
        printScooterVector(reservedScooters);

    } else {
        cout << "\nThere are no reserved scooters!\n\n";
    }
}


void UI::printScooterVector(const vector<Scooter> &scooterVector) {
    cout << '\n';
    int index = 1;
    for (const auto &scooter: scooterVector) {
        cout << index << ". " << scooter.toString() << '\n';
        index++;
    }
    cout << '\n';
}


void UI::showAllInUseScooter() {
    cout << "~~~~ In use scooters ~~~~\n";

    vector<Scooter> inUseScooters = user.getAllInUseScooters();
    if (!inUseScooters.empty()) {
        cout << "Here is a list of all scooters that are in your use:\n";
        printScooterVector(inUseScooters);

    } else {
        cout << "\nYou have no scooters in use!\n\n";
    }
}


void UI::parkScooter() {
    cout << "~~~~ In use scooters ~~~~\n";

    vector<Scooter> inUseScooters = user.getAllInUseScooters();
    if (!inUseScooters.empty()) {
        cout << "Here is a list of all scooters that are in your use:\n";
        printScooterVector(inUseScooters);

        string scooterId;
        cout << "Enter the id of the scooter you want to park: ";
        cin >> scooterId;

        for (const auto &scooter : inUseScooters) {
            if (scooter.getId() == scooterId) {
                // TODO astea si eventual un user repo
//                controller.parkScooter(scooterId);
//                user.removeScooter(scooterId);
            }
        }

    } else {
        cout << "\nYou have no scooters in use!\n\n";
    }
}

