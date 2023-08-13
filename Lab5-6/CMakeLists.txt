cmake_minimum_required(VERSION 3.25)
project(OOP_Lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(OOP_Lab5 main.cpp Scooter.h Scooter.cpp UI.cpp InMemoryRepository.cpp Controller.cpp Tests.cpp Controller.cpp Controller.h CSVFIleRepository.cpp Domain.h User.cpp)
