#pragma once


#include "Scooter.h"
#include <vector>


using Domain::Scooter, std::vector;


namespace Repository {
    class IRepository {
    public:
        virtual void add(const Scooter &newObject) = 0;

        // removes an object from the vector, returns false if the object wasn't found
        virtual void remove(const Scooter &removedObject) = 0;

        // returns the vector of objects
        virtual std::vector<Scooter> getAll() = 0;

        // returns the object with the corresponding index
        virtual Scooter getById(const string &objectId) = 0;

        // updates the specified entity, returns false if the entity wasn't found
        virtual void update(const Scooter &updatedObject) = 0;
    };
}