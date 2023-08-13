#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "CSVFileRepository.h"
#include "ownermenu.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ownerMenu = std::make_unique<OwnerMenu>();
    connect(ownerMenu.get(), &OwnerMenu::showMainWindow, this, &MainWindow::showMainWindowAgain);

    customerMenu = std::make_unique<CustomerMenu>();
    connect(customerMenu.get(), &CustomerMenu::showMainWindow, this, &MainWindow::showMainWindowAgain);
    ui->lePassword->setEchoMode(QLineEdit::Password); //make the password invisible
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cmbFileType_currentIndexChanged(int index)
{
    if (ui->cmbFileType->currentText() == "CSV") {
        ownerMenu->repo = std::make_shared<Repository::CSVRepository>();
        ownerMenu->controller = std::make_shared<Controller::Ctr>(ownerMenu->repo);
    } else {
        customerMenu->repo = std::make_shared<Repository::InMemoryRepository>();
        customerMenu->controller = std::make_shared<Controller::Ctr>(customerMenu->repo);
    }
}


void MainWindow::on_pbLogin_clicked()
{
    string username = ui->leUsername->text().toStdString();
    string userPassword = ui->lePassword->text().toStdString();

    if (username == "owner" && userPassword == "s8cr8t") {
        user = User("owner", "s8cr8t");

        this->hide();
        ownerMenu->show();
    }else if(username == "customer" && userPassword == "tr1ck"){
        user = User("customer", "tr1ck");

        this->hide();
        customerMenu->show();
    }
}


void MainWindow::showMainWindowAgain()
{
    this->show();
}

