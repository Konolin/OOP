#include "Controller.h"
#include <utility>
#include <exception>


using Controller::Ctr, std::invalid_argument, Domain::compareDateAscending, std::exception, Domain::statusToString;


Ctr::Ctr(shared_ptr<IRepository> repoObj) : repository(std::move(repoObj)) {}


void Ctr::dataCheck(const string &id, const string &model, Date commissionDate, int mileage,
                    const string &lastLocation) {
    // check if the id has exactly 3 letters
    if (id.length() != 3 || !hasThreeLetters(id)) {
        throw invalid_argument("The id is not valid.");
    }

    // check if model is valid
    if (model.empty()) {
        throw invalid_argument("Model can not be an empty string.");
    }

    // check if the commission date is valid
    if (commissionDate.day < 1 || commissionDate.day > 31) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (commissionDate.day == 31 && commissionDate.month % 2 == 0) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (commissionDate.day > 28 && commissionDate.month == 2 && commissionDate.year % 4 != 0) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (commissionDate.day > 29 && commissionDate.month == 2 && commissionDate.year % 4 == 0) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (commissionDate.month < 1 || commissionDate.month > 12) {
        throw invalid_argument("Commission date month is not valid.");
    }
    if (commissionDate.year > 2023) {
        throw invalid_argument("Commission date year is not valid.");
    }

    // check if mileage is valid
    if (mileage < 0) {
        throw invalid_argument("Mileage can not be negative.");
    }

    // check if lastLocation is valid
    if (lastLocation.empty()) {
        throw invalid_argument("The last location can not be an empty string.");
    }
}


bool Ctr::add(const string &id, const string &model, const Date &commissionDate, int mileage,
              const string &lastLocation, const Status &status) {
    try {
        dataCheck(id, model, commissionDate, mileage, lastLocation);
        Scooter scooter(id, model, commissionDate, mileage, lastLocation, status);
        repository->add(scooter);
        return true;

    } catch (std::exception &e) {
        return false;
    }
}


bool Ctr::remove(const string &id) {
    if (!hasThreeLetters(id) && id.size() != 3) {
        throw invalid_argument("Id is invalid.");
    }

    for (auto &scooter: repository->getAll()) {
        if (scooter.getId() == id) {
            repository->remove(scooter);
            return true;
        }
    }
    return false;
}


bool Ctr::edit(const string &id, const string &attribute, const string &newAttribute) {
    try {
        Scooter scooter = repository->getById(id);

        if (attribute == "mileage") {
            int newMileage = stoi(newAttribute);
            scooter.setMileage(newMileage);

        } else if (attribute == "lastLocation") {
            scooter.setLastLocation(newAttribute);

        } else if (attribute == "status") {
            Status newStatus;
            if (newAttribute == "parked") {
                newStatus = Status::parked;
                scooter.setStatus(newStatus);
            } else if (newAttribute == "in use") {
                newStatus = Status::inUse;
                scooter.setStatus(newStatus);
            } else if (newAttribute == "in maintenance") {
                newStatus = Status::inMaintenance;
                scooter.setStatus(newStatus);
            } else if (newAttribute == "out of service") {
                newStatus = Status::outOfService;
                scooter.setStatus(newStatus);
            } else if (newAttribute == "reserved") {
                newStatus = Status::reserved;
                scooter.setStatus(newStatus);
            } else {
                return false;
            }

        } else {
            return false;  // Invalid attribute
        }
        repository->update(scooter);
        return true;

    } catch (exception &e) {
        return false;  // Failed to edit scooter
    }
}

vector<Scooter> Ctr::sortedByCommissionDate() {
    vector<Scooter> sortedVector = repository->getAll();

    std::sort(sortedVector.begin(), sortedVector.end(), [](const Scooter &s1, const Scooter &s2) {
        return compareDateAscending(s1.getCommissionDate(), s2.getCommissionDate());
    });

    return sortedVector;
}


bool Ctr::reserveScooter(const string &id) {
    try {
        Scooter scooter = repository->getById(id);

        if (scooter.getStatus() == Domain::parked) {
            scooter.setStatus(Domain::reserved);
            repository->update(scooter);
            return true;
        }
        return false;
    } catch (std::exception &e) {
        return false;
    }
}


bool Ctr::useScooter(const string &id) {
    try {
        Scooter scooter = repository->getById(id);

        if (scooter.getStatus() == Domain::parked) {
            scooter.setStatus(Domain::inUse);
            repository->update(scooter);
            return true;
        }
        return false;
    } catch (std::exception &e) {
        return false;
    }
}


bool Ctr::hasThreeLetters(const string &id) {
    int count = 0;
    for (char c: id) {
        if (std::isalpha(c)) count++;
    }
    return count == 3;
}


vector<Scooter> Ctr::findAvailableScooters() {
    vector<Scooter> availableScooters;

    for (const auto &scooter: repository->getAll()) {
        if (scooter.getStatus() == Domain::parked) {
            availableScooters.push_back(scooter);
        }
    }

    return availableScooters;
}


vector<Scooter> Ctr::searchByLocation(const string &location) {
    vector<Scooter> allScooters = repository->getAll();
    vector<Scooter> filteredScooters;

    for (const auto &scooter: allScooters) {
        if (scooter.getLastLocation().find(location) != string::npos) {
            filteredScooters.push_back(scooter);
        }
    }

    return filteredScooters;
}

vector<Scooter> Ctr::filterScooterDate(const Date &date) {
    vector<Scooter> allScooters = repository->getAll();
    vector<Scooter> filteredScooters;

    for (const auto &scooter: allScooters) {
        Date scooterDate = scooter.getCommissionDate();

        if (scooterDate.year == date.year && scooterDate.month == date.month && scooterDate.day < date.day ||
            scooterDate.year == date.year && scooterDate.month < date.month || scooterDate.year < date.year) {
            filteredScooters.push_back(scooter);
        }
    }

    return filteredScooters;
}

vector<Scooter> Ctr::filterScooterMileage(int mileage) {
    vector<Scooter> allScooters = repository->getAll();
    vector<Scooter> filteredScooters;

    for (const auto &scooter: allScooters) {
        if (scooter.getMileage() < mileage) {
            filteredScooters.push_back(scooter);
        }
    }

    return filteredScooters;
}


