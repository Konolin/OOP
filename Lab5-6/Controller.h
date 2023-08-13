#pragma once


#include <memory>
#include "InMemoryRepository.h"
#include "Repository.h"
#include "Scooter.h"


using std::shared_ptr, Repository::InMemoryRepository, Domain::Date, Domain::Status, Repository::IRepository;


namespace Controller {
    enum UserRole {
        customer, admin
    };

    class Ctr {
    private:
        // check if the data given as parameter is valid
        static void dataCheck(const string &id, const string &model, Date commissionDate, int mileage,
                              const string &lastLocation);

    public:
        shared_ptr<IRepository> repository;

        // constructor
        Ctr(shared_ptr<IRepository> repoObj);

        // creates a new object and adds it to the repository
        bool add(const string &id, const string &model, const Date &commissionDate, int mileage,
                 const string &lastLocation, const Status &status);

        // removes a scooter
        bool remove(const string &id);

        // edits an attribute of the scooter
        bool edit(const string& id, const string& attribute, const string& newAttribute);

        // sorts the vector by the commission date in ascending order
        vector<Scooter> sortedByCommissionDate();

        // changes the status of a scooter to reserved
        bool reserveScooter(const string &id);

        // changes the status of a scooter to inUse
        bool useScooter(const string &id);

        // checks if a string contains 3 letters
        static bool hasThreeLetters(const string &id);

        // returns a vector of scooter that have the status parked
        vector<Scooter> findAvailableScooters();

        // returns a vector of scooters with the matching location
        vector<Scooter> searchByLocation(const string &location);

        // returns a vector of scooters with the date earlier than the parameter
        vector<Scooter> filterScooterDate(const Date &date);

        // returns a vector of scooters with the mileage lower than the parameter
        vector<Scooter> filterScooterMileage(int mileage);
    };
}
