#pragma once


#include "Repository.h"
#include <string>


using Repository::IRepository, std::string;


namespace Repository {
    class CSVRepository : public IRepository {
    private:
        string fileName{};
        vector<Scooter> scooterVector{};

        vector<Scooter> readFromCSV();

        void writeToCSV();

    public:
        CSVRepository();

        // adds a scooter in the repo
        void add(const Scooter &newObject) override;

        // removes an object from the vector, returns false if the object wasn't found
        void remove(const Scooter &removedObject) override;

        // returns the vector of objects
        vector<Scooter> getAll() override;

        // returns the object with the corresponding index
        Scooter getById(const string &objectId) override;

        // updates the specified entity, returns false if the entity wasn't found
        void update(const Scooter &updatedEntity) override;
    };
}

