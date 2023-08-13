#pragma once


#include "Domain.h"
#include "Scooter.h"
#include <string>
#include <vector>


using std::string, Domain::Scooter, std::vector, Domain::User;


namespace Domain {
    class User {
    private:
        string username{};
        string password{};
        vector<Scooter> reservedScooters{};
        vector<Scooter> inUseScooters{};

    public:
        explicit User(const string &username = "None", const string &password = "None");

        [[nodiscard]] string getName() const;

        [[nodiscard]] string getPassword() const;

        void setName(const string &newName);

        void setPassword(const string &newPassword);

        void addReservedScooter(const Scooter &reservedScooter);
        
        vector<Scooter> getAllReservedScooters();

        void addInUseScooter(const Scooter &inUseScooter);

        vector<Scooter> getAllInUseScooters();
    };
}
