#include <string>

using std::string;

class DSM {
private:
    int elementCount;
    int capacity;
    string *elementNames;
    int **adjMatrix;

    static const int RESIZE_FACTOR = 2;

    void resize();

    int elementIndex(const string &elementName);

public:
    DSM(int elementCount);

    DSM(string *elementNames, int elementCount);

    DSM(DSM &original);

    ~DSM();

    int size() const;

    string getName(int index);

    void setElementName(int index, const string &elementName);

    void addLink(const string &fromElement, const string &toElement, int weight);

    void deleteLink(const string &fromElement, const string &toElement);

    bool hasLink(const string &fromElement, const string &toElement);

    int linkWeight(const string &fromElement, const string &toElement);

    int countToLinks(const string &elementName);

    int countFromLinks(const string &elementName);

    int countAllLinks();

    void printAll();

    static DSM loadFromFile(const string &fileName);

    void storeToFile(const string& fileName);

    bool operator==(const DSM &other);
};
