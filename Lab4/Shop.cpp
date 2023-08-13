#include "UI/FruitUI.h"

int main() {
    Repository fruitRepo;
    Controller ctr(fruitRepo);
    UI ui(ctr);

    ui.mainMenu();
    return 0;
}
