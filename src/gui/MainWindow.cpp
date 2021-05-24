#include "Actions.hpp"
#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget* parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

BoardWidget* MainWindow::boardWidget() const {
    return ui->boardWidget;
}

void MainWindow::setRenderer(IRenderer* const renderer) {
    ui->boardWidget->setRenderer(renderer);
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
