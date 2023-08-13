#include "CSVFileRepository.h"
#include <fstream>
#include <string>
#include <sstream>


using Repository::CSVRepository, std::to_string, std::runtime_error, Domain::Status;


CSVRepository::CSVRepository() {
    fileName = "Scooters.csv";
    scooterVector = readFromCSV();
}


void CSVRepository::add(const Scooter &newObject) {
    std::ofstream file(fileName, std::ios::app);

    if (!file.is_open()) {
        throw runtime_error("File could not be opened to open for writing.");
    }

    file << newObject.toString() << "\n";
    scooterVector.push_back(newObject);

    file.close();
}


void CSVRepository::remove(const Scooter &removedObject) {
    for (int i = 0; i < scooterVector.size(); i++) {
        if (scooterVector[i] == removedObject) {
            scooterVector.erase(scooterVector.begin() + i);
            writeToCSV();
            return;
        }
    }
}


vector<Scooter> CSVRepository::getAll() { return scooterVector; }


Scooter CSVRepository::getById(const string &objectId) {
    for (const auto &scooter : scooterVector) {
        if (scooter.getId() == objectId) {
            return scooter;
        }
    }
    throw runtime_error("Scooter was not found.");
}


void CSVRepository::update(const Scooter &updatedEntity) {
    bool found = false;
    for (auto & scooter : scooterVector) {
        if (scooter.getId() == updatedEntity.getId()) {
            scooter = updatedEntity;
            found = true;
        }
    }
    if (found) {
        writeToCSV();
    }
    else {
        throw runtime_error("");
    }
}


vector<Scooter> CSVRepository::readFromCSV() {
    vector<Scooter> readVector;

    std::ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        throw runtime_error("Unable to open file for reading.");
    }

    string line;
    while (getline(inputFile, line)) {
        string id, model, commissionDateDay, commissionDateMonth, commissionDateYear, mileageStr, lastLocation, statusStr;

        std::stringstream ss(line);
        getline(ss, id, ',');
        getline(ss, model, ',');
        getline(ss, commissionDateDay, '-');
        getline(ss, commissionDateMonth, '-');
        getline(ss, commissionDateYear, ',');
        getline(ss, mileageStr, ',');
        getline(ss, lastLocation, ',');
        getline(ss, statusStr, '\n');

        Domain::Date commissionDateObj{};
        commissionDateObj.day = stoi(commissionDateDay);
        commissionDateObj.month = stoi(commissionDateMonth);
        commissionDateObj.year = stoi(commissionDateYear);
        int mileage = stoi(mileageStr);
        Status status = Domain::stringToStatus(statusStr);

        // Create a Scooter object and add it to the vector
        readVector.emplace_back(id, model, commissionDateObj, mileage, lastLocation, status);
    }
    inputFile.close();

    return readVector;
}

void CSVRepository::writeToCSV() {
    std::ofstream file(fileName, std::ios::out);

    if (!file.is_open()) {
        throw runtime_error("File could not be opened.");
    }

    for (const auto &scooter: scooterVector) {
        file << scooter.toString() << '\n';
    }

    file.close();
}

