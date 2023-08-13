#pragma once


#include "Repository.h"


namespace Repository {
    class InMemoryRepository : public IRepository{
    private:
        vector<Scooter> scooterVector{};

        void generateDummyData();

    public:
        // constructor
        InMemoryRepository();

        // adds a scooter to the vector
        void add(const Scooter &new_scooter) override;

        // removes a scooter from the vector, returns false if the entity wasn't found
        void remove(const Scooter &scooter) override;

        // returns the vector of scooters
        vector<Scooter> getAll() override;

        // returns the scooter with the corresponding index
        Scooter getById(const string &id) override;

        // updates the specified entity
        void update(const Scooter &updatedEntity) override;
    };
}
