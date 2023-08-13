#include "User.h"


using Domain::User;


User::User(const string &_username, const string &_password) {
    username = _username;
    password = _password;
}


string User::getName() const { return username; }


string User::getPassword() const { return password; }


void Domain::User::setName(const string &newName) {
    username = newName;
}


void Domain::User::setPassword(const string &newPassword) {
    password = newPassword;
}


void User::addReservedScooter(const Scooter &reservedScooter) {
    reservedScooters.push_back(reservedScooter);
}


vector<Scooter> User::getAllReservedScooters() {
    return reservedScooters;
}


void User::addInUseScooter(const Scooter &inUseScooter) {
    inUseScooters.push_back(inUseScooter);
}


vector<Scooter> User::getAllInUseScooters() {
    return inUseScooters;
}
