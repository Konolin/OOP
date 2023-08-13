cmake_minimum_required(VERSION 3.24)
project(Lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab4 UI/FruitUI.h UI/FruitUI.cpp Repository/FruitRepo.cpp Repository/FruitRepo.h Domain/Fruit.h Domain/Fruit.cpp Controller/FruitController.cpp Controller/FruitController.h Shop.cpp Tests/allTests.h Tests/allTests.cpp)
