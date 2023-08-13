#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "User.h"
#include "customermenu.h"
#include "ownermenu.h"
#include <memory.h>

using std::string;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cmbFileType_currentIndexChanged(int index);

    void on_pbLogin_clicked();

    void showMainWindowAgain();

private:
    Ui::MainWindow *ui;
    string usertname;
    string password;
    std::shared_ptr<OwnerMenu> ownerMenu;
    std::shared_ptr<CustomerMenu> customerMenu;
    User user;
};
#endif // MAINWINDOW_H
