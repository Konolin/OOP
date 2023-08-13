#pragma once

#include "../Domain/Fruit.h"
#include <vector>

using std::vector;

class Repository {
private:
    vector<Fruit> fruitVector;

    void dummyData();

public:
    Repository();

    void addFruit(const Fruit &addedFruit);

    void deleteFruit(const Fruit &deletedFruit);

    vector<Fruit> getAll();
};
