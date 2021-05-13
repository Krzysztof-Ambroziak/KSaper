#include "Definitions.hpp"
#include "controller/Controller.hpp"
#include "src/gui/MainWindow.hpp"
#include "src/model/Model.hpp"
#include "src/renderer/Renderer.hpp"

#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    QApplication::setOrganizationName(ksaper::ORGANIZATION);
    QApplication::setApplicationName(ksaper::APPLICATION);
    
    MainWindow mainWindow;
    Model model;
    Renderer renderer;
    Controller controller(&model, &mainWindow, &renderer);
    controller.start();
    
    return QApplication::exec();
}
