#include "customermenu.h"
#include "ui_customermenu.h"
#include <vector>

CustomerMenu::CustomerMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CustomerMenu)
{
    repo = std::make_shared<Repository::InMemoryRepository>();
    controller = std::make_shared<Controller::Ctr>(repo);

    ui->setupUi(this);

    hideSecundaryUi();
}


CustomerMenu::~CustomerMenu()
{
    delete ui;
}


void CustomerMenu::on_pbSearch_clicked()
{    
    hideSecundaryUi();
    showListUi(true);
    ui->pbSearchGo->setText("Search");
    on_pbSearchGo_clicked();
}


void CustomerMenu::on_pbReserve_clicked()
{
    ui->leEnterID->clear();
    hideSecundaryUi();
    showIDInputUi();
    ui->pbGo->setText("Reserve");
    on_pbGo_clicked();
}

void CustomerMenu::on_pbUse_clicked()
{
    ui->leEnterID->clear();
    hideSecundaryUi();
    showIDInputUi();
    ui->pbGo->setText("Use");
    on_pbGo_clicked();
}

void CustomerMenu::on_pbPark_clicked()
{
    ui->leEnterID->clear();
    hideSecundaryUi();
    showIDInputUi();
    ui->pbGo->setText("Park");
    on_pbGo_clicked();
}


void CustomerMenu::on_pbAllReserved_clicked()
{
    hideSecundaryUi();
    showListUi(false);
    vector<Scooter> allReservedScooters = user.getAllReservedScooters();
    controller->populateViewList(ui->listViewAll, allReservedScooters);
}

void CustomerMenu::on_pbAllInUse_clicked()
{
    hideSecundaryUi();
    showListUi(false);
    vector<Scooter> allInUseScooters = user.getAllInUseScooters();
    controller->populateViewList(ui->listViewAll, allInUseScooters);
}


void CustomerMenu::on_pbFilter_clicked()
{
    hideSecundaryUi();
    showFilterUi();
}


void CustomerMenu::on_pbMileage_clicked()
{
    showListUi(true);
    ui->pbSearchGo->setText("Filter mileage");
    on_pbSearchGo_clicked();
}


void CustomerMenu::on_pbAge_clicked()
{
    showListUi(true);
    ui->pbSearchGo->setText("Filter age");
    on_pbSearchGo_clicked();
}


void CustomerMenu::on_pbSearchGo_clicked()
{
    if (ui->pbSearchGo->text() == "Search") {
        string stringLocation = ui->leInput->text().toStdString();
        vector<Scooter> filteredVector = controller->searchByLocation(stringLocation);

        controller->populateViewList(ui->listViewAll, filteredVector);
    }

    if (ui->pbSearchGo->text() == "Filter age") {
        string stringDate = ui->leInput->text().toStdString();
        if (stringDate != "") {
            Date date = Domain::stringToDate(stringDate);
            vector<Scooter> filteredVector = controller->filterScooterDate(date);

            controller->populateViewList(ui->listViewAll, filteredVector);
        }
    }

    if (ui->pbSearchGo->text() == "Filter mileage") {
        vector<Scooter> filteredVector = controller->filterScooterMileage(ui->leInput->text().toInt());
        controller->populateViewList(ui->listViewAll, filteredVector);
    }

}

void CustomerMenu::on_pbGo_clicked()
{
    if (ui->pbGo->text() == "Reserve"){
        ui->lwParkedScootes->show();
        vector <Scooter> parkedScooters = controller->getAllParkedScooters();
        controller->populateViewList(ui->lwParkedScootes, parkedScooters);
        string id = ui->leEnterID->text().toStdString();
        if (controller->reserveScooter(id)){
            user.addReservedScooter(controller->repository->getById(id));
            ui->pbGo->setText("Successfully reserved");
        }else
            ui->pbGo->setText("error");

    }

    if (ui->pbGo->text() == "Use"){
        ui->lwParkedScootes->show();
        vector <Scooter> parkedScooters = controller->getAllParkedScooters();
        controller->populateViewList(ui->lwParkedScootes, parkedScooters);

        string id = ui->leEnterID->text().toStdString();
        if (controller->useScooter(id)){
            user.addInUseScooter(controller->repository->getById(id));
            ui->pbGo->setText("In use");
        }

    }

    if (ui->pbGo->text() == "Park"){
        string id = ui->leEnterID->text().toStdString();
        if (controller->parkScooter(id)){
            ui->pbGo->setText("Done");
            user.removeInUseScooter(controller->repository->getById(id));
        }
    }
}



void CustomerMenu::hideListUi() {
    ui->listViewAll->hide();
    ui->lScooterList->hide();
    ui->lInput->hide();
    ui->leInput->hide();
    ui->pbSearchGo->hide();
}


void CustomerMenu::showListUi(bool input) {
    ui->listViewAll->show();
    ui->lScooterList->show();

    if (input) {
        showInputUi();
    }
}


void CustomerMenu::hideFilterUi() {
    ui->pbMileage->hide();
    ui->pbAge->hide();
}


void CustomerMenu::showFilterUi() {
    ui->pbMileage->show();
    ui->pbAge->show();
}

void CustomerMenu::hideAllReservedUi()
{
    ui->listViewAll->hide();
    ui->lReservedScooters->hide();
}

void CustomerMenu::showAllReservedUi()
{
    ui->listViewAll->show();
    ui->lReservedScooters->show();

}

void CustomerMenu::hideAllUsedUi()
{
    ui->listViewAll->hide();
    ui->lInUseScooters->hide();
}

void CustomerMenu::hideReserveUi()
{

    ui->lReserve->hide();
    ui->lEnterID->hide();
    ui->leEnterID->hide();
    ui->pbGo->hide();
}

void CustomerMenu::hideUseUi()
{

    ui->lUse->hide();
    ui->lEnterID->hide();
    ui->leEnterID->hide();
    ui->pbGo->hide();

}

void CustomerMenu::hideParkUi()
{

    ui->lPark->hide();
    ui->lEnterID->hide();
    ui->leEnterID->hide();
    ui->pbGo->hide();

}

void CustomerMenu::hideSecundaryUi() {
    hideListUi();
    hideFilterUi();
    hideAllReservedUi();
    hideAllUsedUi();
    hideReserveUi();
    hideUseUi();
    hideParkUi();
    hideAllUsedUi();
    hideAllReservedUi();
    ui->lwParkedScootes->hide();

}


void CustomerMenu::showInputUi() {
    ui->lInput->show();
    ui->leInput->show();
    ui->pbSearchGo->show();
}

void CustomerMenu::showIDInputUi()
{
    ui->leEnterID->show();
    ui->lEnterID->show();
    ui->pbGo->show();

}


void CustomerMenu::on_pbReturn_clicked()
{
    hideSecundaryUi();
    this->hide();
    emit showMainWindow();
}
