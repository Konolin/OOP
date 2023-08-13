#ifndef CUSTOMERMENU_H
#define CUSTOMERMENU_H

#include "Controller.h"
#include "Repository.h"
#include "User.h"
#include <QMainWindow>

namespace Ui {
class CustomerMenu;
}

class CustomerMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomerMenu(QWidget *parent = nullptr);
    ~CustomerMenu();
    std::shared_ptr<Repository::IRepository> repo;
    std::shared_ptr<Controller::Ctr> controller;
    Domain::User user{};

private slots:
    void on_pbReturn_clicked();

    void on_pbSearch_clicked();

    void on_pbReserve_clicked();

    void on_pbUse_clicked();

    void on_pbPark_clicked();

    void on_pbAllReserved_clicked();

    void on_pbAllInUse_clicked();

    void on_pbFilter_clicked();

    void on_pbMileage_clicked();

    void on_pbAge_clicked();

    void on_pbGo_clicked();

    void on_pbSearchGo_clicked();


private:
    Ui::CustomerMenu *ui;

    void hideListUi();

    void showListUi(bool input);

    void hideFilterUi();

    void showFilterUi();

    void hideReserveUi();

    void showReserveUi();

    void hideSecundaryUi();

    void showInputUi();

    void showIDInputUi();

    void hideUseUi();

    //void showUseUi();

    //void showParkUi();

    void hideParkUi();

    void hideAllReservedUi();

    void showAllReservedUi();

    void hideAllUsedUi();

signals:
    void showMainWindow();
};

#endif // CUSTOMERMENU_H
