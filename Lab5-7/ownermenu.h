#ifndef OWNERMENU_H
#define OWNERMENU_H

#include "Controller.h"
#include "Repository.h"
#include <QMainWindow>

namespace Ui {
class OwnerMenu;
}

class OwnerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit OwnerMenu(QWidget *parent = nullptr);
    ~OwnerMenu();
    std::shared_ptr<Repository::IRepository> repo;
    std::shared_ptr<Controller::Ctr> controller;

private slots:
    void on_pbReturn_clicked();

    void on_pbAdd_clicked();

    void on_pbView_clicked();

    void on_pbFilter_clicked();

    void on_pbMileage_clicked();

    void on_pbAge_clicked();

    void on_pbSearch_clicked();

    void on_pbGo_clicked();

    void on_pbAddConfirm_clicked();

    void on_pbRemove_clicked();

    void on_pbEdit_clicked();

    void on_pbEditInputId_clicked();

    void on_pbEditGo_clicked();

private:
    Ui::OwnerMenu *ui;

    const QString deleteSentence = "Enter the id of the scooter you want to delete:";

    void hideListUi();

    void showListUi(bool input);

    void hideFilterUi();

    void showFilterUi();

    void hideAddUi();

    void showAddUi();

    void hideSecundaryUi();

    void showInputUi();

    void hideEditUi();

    void showEditUi();

signals:
    void showMainWindow();
};

#endif // OWNERMENU_H
