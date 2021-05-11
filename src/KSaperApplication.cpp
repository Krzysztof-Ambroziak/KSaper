#include "Definitions.hpp"
#include "controller/Controller.hpp"
#include "src/gui/MainWindow.hpp"
#include "src/model/Model.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QApplication::setOrganizationName(ksaper::ORGANIZATION);
    QApplication::setApplicationName(ksaper::APPLICATION);
    
    MainWindow mainWindow;
    Model model;
    Controller controller(&model, &mainWindow);
    controller.start();
    
    return QApplication::exec();
}
