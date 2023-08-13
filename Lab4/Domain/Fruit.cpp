#include "Fruit.h"
#include <stdexcept>
#include <utility>


Fruit::Fruit(string _name, string _origin, Date _expDate, int _quantity, float _price) {
    name = std::move(_name);
    origin = std::move(_origin);
    expDate = _expDate;
    quantity = _quantity;
    price = _price;
}


string Fruit::getName() const { return name; }


string Fruit::getOrigin() const { return origin; }


Date Fruit::getExpDate() const { return expDate; }


float Fruit::getPrice() const { return price; }


int Fruit::getQuantity() const { return quantity; }


void Fruit::setPrice(float newPrice) {
    if (newPrice < 0)
        throw std::invalid_argument("Negative prices are not valid.");
    price = newPrice;
}


void Fruit::setQuantity(int newQuantity) {
    if (newQuantity < 0)
        throw std::invalid_argument("Negative quantities are not valid.");
    quantity = newQuantity;
}
