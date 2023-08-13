#include "Scooter.h"
#include "Controller.h"


using Domain::Scooter, Domain::Date, Domain::Status, Controller::Ctr, std::invalid_argument, std::to_string;


Scooter::Scooter(const string &_id, const string &_model, Date _commissionDate, int _mileage,
                 const string &_lastLocation, Status _status) {
    id = _id;
    model = _model;
    commissionDate = _commissionDate;
    mileage = _mileage;
    lastLocation = _lastLocation;
    status = _status;
}


string Scooter::getId() const { return id; }


string Scooter::getModel() const { return model; }


Date Scooter::getCommissionDate() const { return commissionDate; }


int Scooter::getMileage() const { return mileage; }


string Scooter::getLastLocation() const { return lastLocation; }


Status Scooter::getStatus() const { return status; }


void Scooter::setId(const string &newId) {
    if (Ctr::hasThreeLetters(newId) && newId.size() == 3) {
        id = newId;
    } else {
        throw invalid_argument("The id does not respect the convention (3 letters).");
    }
}


void Scooter::setModel(const string &newModel) {
    if (!newModel.empty()) {
        model = newModel;
    } else {
        throw invalid_argument("Model can not be empty.");
    }
}


void Scooter::setCommissionDate(const Date &newCommissionDate) {
    if (newCommissionDate.day < 1 || newCommissionDate.day > 31) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (newCommissionDate.day == 31 && newCommissionDate.month % 2 == 0) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (newCommissionDate.day > 28 && newCommissionDate.month == 2 && newCommissionDate.year % 4 != 0) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (newCommissionDate.day > 29 && newCommissionDate.month == 2 && newCommissionDate.year % 4 == 0) {
        throw invalid_argument("Commission date day is not valid.");
    }
    if (newCommissionDate.month < 1 || newCommissionDate.month > 12) {
        throw invalid_argument("Commission date month is not valid.");
    }
    if (newCommissionDate.year > 2023) {
        throw invalid_argument("Expiration date year is not valid.");
    }

    commissionDate = newCommissionDate;
}


void Scooter::setMileage(int newMileage) {
    if (newMileage > 0) {
        mileage = newMileage;
    } else {
        throw invalid_argument("Mileage can not be negative.");
    }
}


void Scooter::setLastLocation(const string &newLastLocation) {
    if (!newLastLocation.empty()) {
        lastLocation = newLastLocation;
    } else {
        throw invalid_argument("The last location can not be empty.");
    }
}


void Scooter::setStatus(const Status &newStatus) {
    status = newStatus;
}


bool Scooter::operator==(const Scooter &other) {
    if (id != other.id) { return false; }
    if (model != other.model) { return false; }
    if (commissionDate.day != other.commissionDate.day) { return false; }
    if (commissionDate.month != other.commissionDate.month) { return false; }
    if (commissionDate.year != other.commissionDate.year) { return false; }
    if (mileage != other.mileage) { return false; }
    if (lastLocation != other.lastLocation) { return false; }
    if (status != other.status) { return false; }

    return true;
}


bool Scooter::operator!=(const Scooter &other) {
    return !operator==(other);
}


string Scooter::toString() const {
    string strCommissionDate = Domain::dateToString(commissionDate);
    string strMileage = to_string(mileage);
    string strStatus = statusToString(status);

    string scooterString =
            id + ',' + model + ',' + strCommissionDate + ',' + strMileage + ',' + lastLocation + ',' + strStatus;

    return scooterString;
}


bool Domain::compareDateAscending(const Date &date1, const Date &date2) {
    if (date1.year != date2.year) {
        return date1.year < date2.year;
    }

    if (date1.month != date2.month) {
        return date1.month < date2.month;
    }

    return date1.day < date2.day;
}


string Domain::statusToString(const Domain::Status &status) {
    switch (status) {
        case parked:
            return "parked";
        case reserved:
            return "reserved";
        case inUse:
            return "in use";
        case inMaintenance:
            return "in maintenance";
        default:
            return "out of service";
    }
}


Status Domain::stringToStatus(const string& statusStr) {
    if (statusStr == "parked") {
        return Status::parked;
    } else if (statusStr == "reserved") {
        return Status::reserved;
    } else if (statusStr == "in use") {
        return Status::inUse;
    } else if (statusStr == "in maintenance") {
        return Status::inMaintenance;
    } else {
        return Status::outOfService;
    }
}


string Domain::dateToString(const Date &date) {
    return to_string(date.day) + '-' + to_string(date.month) + '-' + to_string(date.year);
}
