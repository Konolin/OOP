#include "ownermenu.h"
#include "ui_ownermenu.h"
#include <vector>

OwnerMenu::OwnerMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::OwnerMenu)
{
    repo = std::make_shared<Repository::InMemoryRepository>();
    controller = std::make_shared<Controller::Ctr>(repo);

    ui->setupUi(this);

    hideSecundaryUi();
}


OwnerMenu::~OwnerMenu()
{
    delete ui;
}


void OwnerMenu::on_pbAdd_clicked()
{
    hideSecundaryUi();
    showAddUi();
}


void OwnerMenu::on_pbAddConfirm_clicked()
{
    string id = ui->leId->text().toStdString();
    string model = ui->leModel->text().toStdString();

    string dateStr = ui->leDate->text().toStdString();
    Date date{-1,-1,-1};
    if (!dateStr.empty()) {
        date = Domain::stringToDate(dateStr);
    }

    string mileageStr = ui->leMileage->text().toStdString();
    int mileage = -1;
    if (!mileageStr.empty()) {
        mileage = stoi(mileageStr);
    }

    string location = ui->leLocation->text().toStdString();

    string statusStr = ui->leStatus->text().toStdString();
    Status status = Domain::stringToStatus(statusStr);

    if (controller->add(id, model, date, mileage, location, status)) {
        ui->pbAddConfirm->setText("Successfully added");
    } else {
        ui->pbAddConfirm->setText("Failed to add");
    }
}


void OwnerMenu::on_pbRemove_clicked()
{
    hideSecundaryUi();
    showInputUi();
    ui->lDeleteSentence->show();
    ui->pbGo->setText("Remove");
    on_pbGo_clicked();
}


void OwnerMenu::on_pbEdit_clicked()
{
    hideSecundaryUi();
    showEditUi();
}


void OwnerMenu::on_pbEditInputId_clicked()
{
    if (!ui->leEditInputId->text().isEmpty()) {
        string id = ui->leEditInputId->text().toStdString();
        // TODO - invalid id
        Scooter scooter = controller->repository->getById(id);

        QString oldId = "Id: " + QString::fromStdString(scooter.getId());
        QString oldModel = "Model: " + QString::fromStdString(scooter.getModel());
        QString oldDate = "Com. date: " + QString::fromStdString(Domain::dateToString(scooter.getCommissionDate()));
        QString oldMileage = "Mileage: " + QString::number(scooter.getMileage());
        QString oldLocation = "Location: " + QString::fromStdString(scooter.getLastLocation());
        QString oldStatus = "Status: " + QString::fromStdString(Domain::statusToString(scooter.getStatus()));

        ui->lEditId->setText(oldId);
        ui->lEditModel->setText(oldModel);
        ui->lEditDate->setText(oldDate);
        ui->lEditMileage->setText(oldMileage);
        ui->lEditLocation->setText(oldLocation);
        ui->lEditStatus->setText(oldStatus);
    }
}


void OwnerMenu::on_pbEditGo_clicked()
{
    string userInput = ui->leEditInput->text().toStdString();
    string id = ui->leEditInputId->text().toStdString();

    if (ui->cmbEditOption->currentText() == "Mileage") {
        controller->edit(id, "mileage", userInput);
        return;
    }

    if (ui->cmbEditOption->currentText() == "Status") {
        controller->edit(id, "status", userInput);
        return;
    }

    if (ui->cmbEditOption->currentText() == "Last location") {
        controller->edit(id, "lastLocation", userInput);
        return;
    }
}


void OwnerMenu::on_pbSearch_clicked()
{
    hideSecundaryUi();
    showListUi(true);
    ui->pbGo->setText("Search");
    on_pbGo_clicked();
}


void OwnerMenu::on_pbFilter_clicked()
{
    hideSecundaryUi();
    showFilterUi();
}


void OwnerMenu::on_pbView_clicked()
{
    hideSecundaryUi();
    showListUi(false);

    vector<Scooter> allScooters = controller->repository->getAll();
    controller->populateViewList(ui->listViewAll, allScooters);
}


void OwnerMenu::on_pbMileage_clicked()
{
    showListUi(true);
    ui->pbGo->setText("Filter mileage");
    on_pbGo_clicked();
}


void OwnerMenu::on_pbAge_clicked()
{
    showListUi(true);
    ui->pbGo->setText("Filter age");
    on_pbGo_clicked();
}


void OwnerMenu::on_pbGo_clicked()
{
    if (ui->pbGo->text() == "Search") {
        string stringLocation = ui->leInput->text().toStdString();
        vector<Scooter> filteredVector = controller->searchByLocation(stringLocation);

        controller->populateViewList(ui->listViewAll, filteredVector);
    }

    if (ui->pbGo->text() == "Filter age") {
        string stringDate = ui->leInput->text().toStdString();
        if (stringDate != "") {
            Date date = Domain::stringToDate(stringDate);
            vector<Scooter> filteredVector = controller->filterScooterDate(date);

            controller->populateViewList(ui->listViewAll, filteredVector);
        }
    }

    if (ui->pbGo->text() == "Filter mileage") {
        vector<Scooter> filteredVector = controller->filterScooterMileage(ui->leInput->text().toInt());
        controller->populateViewList(ui->listViewAll, filteredVector);
    }

    if (ui->pbGo->text() == "Remove") {
        string input = ui->leInput->text().toStdString();
        if (input != "") {
            QString success;
            if (controller->remove(input)) {
                success = "\nScooter successfully removed.";
            } else {
                success = "\nScooter could not be removed.";
            }
            ui->lDeleteSentence->setText(deleteSentence + success);
        }
    }
}


void OwnerMenu::hideListUi() {
    ui->listViewAll->hide();
    ui->lScooterList->hide();
    ui->lInput->hide();
    ui->leInput->hide();
    ui->pbGo->hide();
}


void OwnerMenu::showListUi(bool input) {
    ui->listViewAll->show();
    ui->lScooterList->show();

    if (input) {
        showInputUi();
    }
}


void OwnerMenu::hideFilterUi() {
    ui->pbMileage->hide();
    ui->pbAge->hide();
}


void OwnerMenu::showFilterUi() {
    ui->pbMileage->show();
    ui->pbAge->show();
}


void OwnerMenu::hideAddUi() {
    ui->lId->hide();
    ui->leId->hide();
    ui->lModel->hide();
    ui->leModel->hide();
    ui->lDate->hide();
    ui->leDate->hide();
    ui->lMileage->hide();
    ui->leMileage->hide();
    ui->lLocation->hide();
    ui->leLocation->hide();
    ui->lStatus->hide();
    ui->leStatus->hide();
    ui->pbAddConfirm->setText("Add");
    ui->pbAddConfirm->hide();
}


void OwnerMenu::showAddUi() {
    ui->lId->show();
    ui->leId->show();
    ui->lModel->show();
    ui->leModel->show();
    ui->lDate->show();
    ui->leDate->show();
    ui->lMileage->show();
    ui->leMileage->show();
    ui->lLocation->show();
    ui->leLocation->show();
    ui->lStatus->show();
    ui->leStatus->show();
    ui->pbAddConfirm->show();
}


void OwnerMenu::hideSecundaryUi() {
    hideListUi();
    hideFilterUi();
    hideAddUi();
    hideEditUi();
    ui->lDeleteSentence->hide();
}


void OwnerMenu::showInputUi() {
    ui->lInput->show();
    ui->leInput->show();
    ui->pbGo->show();
}


void OwnerMenu::on_pbReturn_clicked()
{
    hideSecundaryUi();
    this->hide();
    emit showMainWindow();
}


void OwnerMenu::hideEditUi() {
    ui->lEditId->hide();
    ui->lEditModel->hide();
    ui->lEditDate->hide();
    ui->lEditMileage->hide();
    ui->lEditLocation->hide();
    ui->lEditStatus->hide();
    ui->cmbEditOption->hide();
    ui->lEditOption->hide();
    ui->lEditInput->hide();
    ui->leEditInput->hide();
    ui->lEditInput->hide();
    ui->pbEditGo->hide();
    ui->lEditInputId->hide();
    ui->pbEditInputId->hide();
    ui->leEditInputId->hide();
}


void OwnerMenu::showEditUi() {
    ui->lEditId->show();
    ui->lEditModel->show();
    ui->lEditDate->show();
    ui->lEditMileage->show();
    ui->lEditLocation->show();
    ui->lEditStatus->show();
    ui->cmbEditOption->show();
    ui->lEditOption->show();
    ui->lEditInput->show();
    ui->leEditInput->show();
    ui->lEditInput->show();
    ui->pbEditGo->show();
    ui->lEditInputId->show();
    ui->pbEditInputId->show();
    ui->leEditInputId->show();
}
