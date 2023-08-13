#include "InMemoryRepository.h"
#include "Controller.h"
#include "UI.h"
#include "Tests.h"
#include "mainwindow.h"


#include <QApplication>


using Repository::InMemoryRepository, Controller::Ctr, UserInterface::UI, Test::Tests, std::make_shared;


int main(int argc, char *argv[]) {
//    Tests testsObj;
//    testsObj.testAll();

    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
