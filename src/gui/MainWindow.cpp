#include "Actions.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

void MainWindow::buildMenuAndToolBar(const Actions& actions) {
    auto menuBar = ui->menubar;
    auto menuGame = menuBar->addMenu("&Game");
    menuGame->addAction(actions.newGame);
    
    auto toolbar = ui->toolBar;
    toolbar->addAction(actions.newGame);
}

MainWindow::~MainWindow() {
    delete ui;
}
