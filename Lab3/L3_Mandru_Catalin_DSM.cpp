#include "L3_Mandru_Catalin_DSM.h"
#include <iostream>
#include <exception>
#include <fstream>
#include <sstream>

using namespace std;

DSM::DSM(int elementCount) {
    this->elementCount = 0;
    capacity = elementCount;

    elementNames = new string[elementCount];

    adjMatrix = new int *[elementCount];
    for (int row = 0; row < elementCount; row++)
        adjMatrix[row] = new int[elementCount]{};
}


DSM::DSM(string *elementNames, int elementCount) {
    this->elementCount = elementCount;
    capacity = elementCount;

    this->elementNames = elementNames;

    adjMatrix = new int *[elementCount];
    for (int row = 0; row < elementCount; row++)
        adjMatrix[row] = new int[elementCount]{};
}


DSM::DSM(DSM &original) {
    elementCount = original.elementCount;
    capacity = original.capacity;
    elementNames = original.elementNames;
    adjMatrix = original.adjMatrix;
}


int DSM::size() const { return elementCount; }


string DSM::getName(int index) {
    if (index < elementCount && index >= 0) return elementNames[index];
    throw out_of_range("Invalid index!");
}


void DSM::setElementName(int index, const string &elementName) {
    if (index < elementCount && index >= 0)
        elementNames[index] = elementName;
    else throw out_of_range("Invalid index!");
}


void DSM::addLink(const string &fromElement, const string &toElement, int weight) {
    int fromIndex = elementIndex(fromElement);
    int toIndex = elementIndex(toElement);

    // check if capacity needs to be increased
    if ((fromIndex == -1 || toIndex == -1) && capacity == elementCount) resize();

    // add the nonexistent element
    if (fromIndex == -1) {
        fromIndex = elementCount++;
        elementNames[fromIndex] = fromElement;
    }
    if (toIndex == -1) {
        toIndex = elementCount++;
        elementNames[toIndex] = toElement;
    }

    adjMatrix[fromIndex][toIndex] = weight;
}


void DSM::deleteLink(const string &fromElement, const string &toElement) {
    int fromIndex = elementIndex(fromElement);
    int toIndex = elementIndex(toElement);

    if (fromIndex == -1 || toIndex == -1)
        throw invalid_argument("One or more parameters are not in the matrix!");

    adjMatrix[fromIndex][toIndex] = 0;
}


bool DSM::hasLink(const string &fromElement, const string &toElement) {
    int fromIndex = elementIndex(fromElement);
    int toIndex = elementIndex(toElement);

    if (fromIndex == -1 || toIndex == -1)
        throw invalid_argument("One or more parameters are not in the matrix!");

    return adjMatrix[fromIndex][toIndex] != 0;
}


int DSM::linkWeight(const string &fromElement, const string &toElement) {
    if (hasLink(fromElement, toElement)) {
        int fromIndex = elementIndex(fromElement);
        int toIndex = elementIndex(toElement);
        return adjMatrix[fromIndex][toIndex];
    }
    throw invalid_argument("One or more parameters are not in the matrix!");
}


int DSM::countToLinks(const string &elementName) {
    int index = elementIndex(elementName);

    if (index != -1) {
        int count = 0;
        for (int col = 0; col < elementCount; col++)
            if (adjMatrix[index][col] != 0) count++;
        return count;
    }

    throw invalid_argument("Element given as parameter does not exist!");
}


int DSM::countFromLinks(const string &elementName) {
    int index = elementIndex(elementName);

    if (index != -1) {
        int count = 0;
        for (int row = 0; row < elementCount; row++)
            if (adjMatrix[row][index] != 0) count++;
        return count;
    }

    throw invalid_argument("Element given as parameter does not exist!");
}


int DSM::countAllLinks() {
    int count = 0;
    for (int row = 0; row < elementCount; row++)
        for (int col = 0; col < elementCount; col++)
            if (adjMatrix[row][col] != 0) count++;
    return count;
}


int DSM::elementIndex(const string &elementName) {
    for (int index = 0; index < elementCount; index++)
        if (elementNames[index] == elementName) return index;
    return -1;
}


void DSM::resize() {
    capacity = (capacity + 1) * RESIZE_FACTOR;

    auto *newElementNames = new string[capacity];
    for (int index = 0; index < elementCount; index++)
        newElementNames[index] = elementNames[index];

    int **newAdjMatrix = new int *[capacity];
    for (int row = 0; row < capacity; row++)
        newAdjMatrix[row] = new int[capacity];

    for (int row = 0; row < capacity; row++)
        for (int col = 0; col < capacity; col++)
            if (row < elementCount && col < elementCount)
                newAdjMatrix[row][col] = adjMatrix[row][col];
            else newAdjMatrix[row][col] = 0;

//    delete[] elementNames; // TODO - DE CE BUBUIEEE??????
    elementNames = newElementNames;

    for (int row = 0; row < elementCount; row++) delete[] adjMatrix[row];
    delete[] adjMatrix;
    adjMatrix = newAdjMatrix;
}


void DSM::printAll() {
    cout << "elementNames: ";
    for (int index = 0; index < elementCount; index++)
        cout << elementNames[index] << ", ";
    cout << "\n\n";

    cout << "adjMatrix:\n";
    for (int row = 0; row < elementCount; row++) {
        for (int col = 0; col < elementCount; col++)
            cout << adjMatrix[row][col] << " ";
        cout << "\n";
    }
    cout << "\n";
}


DSM DSM::loadFromFile(const string &fileName) {
    ifstream file(fileName);

    if (!file.is_open()) throw runtime_error("File could not get open!");

    DSM result(0);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string fromElementName, toElementName, weightStr;

        getline(ss, fromElementName, ',');
        getline(ss, weightStr, ',');
        getline(ss, toElementName);

        int weight = stoi(weightStr);

        result.addLink(fromElementName, toElementName, weight);
    }

    file.close();
    return result;
}


void DSM::storeToFile(const string &fileName) {
    ofstream file(fileName);

    if (!file.is_open()) throw runtime_error("File could not get open!");

    for (int fromIndex = 0; fromIndex < elementCount; fromIndex++)
        for (int toIndex = 0; toIndex < elementCount; toIndex++) {
            string fromElement = elementNames[fromIndex];
            string toElement = elementNames[toIndex];

            if (hasLink(fromElement, toElement)) {
                string weight = to_string(linkWeight(fromElement, toElement));
                string line = fromElement + ',' + weight + ',' + toElement + '\n';
                file << line;
            }
        }

    file.close();
}


bool DSM::operator==(const DSM &other) {
    if (elementCount != other.elementCount) return false;

    for (int index = 0; index < elementCount; index++)
        if (elementNames[index] != other.elementNames[index]) return false;

    for (int row = 0; row < elementCount; row++)
        for (int col = 0; col < elementCount; col++)
            if (adjMatrix[row][col] != other.adjMatrix[row][col]) return false;

    return true;
}


DSM::~DSM() {
    for (int row = 0; row < elementCount; row++) delete[] adjMatrix[row];
    delete[] adjMatrix;
    delete[] elementNames;
}
