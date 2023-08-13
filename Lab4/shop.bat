@echo off

g++ -std=c++2a Domain/*.cpp Repository/*.cpp Controller/*.cpp UI/*.cpp Tests/*.cpp Shop.cpp -o shop.exe
shop.exe