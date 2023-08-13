#include "InMemoryRepository.h"
#include "Controller.h"
#include "UI.h"
#include "Tests.h"


using Repository::InMemoryRepository, Controller::Ctr, UserInterface::UI, Test::Tests, std::make_shared;


int main() {
    Tests testsObj;
    testsObj.testAll();

    shared_ptr<IRepository> repo = make_shared<InMemoryRepository>();
    shared_ptr<Ctr> controller = make_shared<Ctr>(repo);
    UI ui(controller);
    ui.startUI();

    return 0;
}

