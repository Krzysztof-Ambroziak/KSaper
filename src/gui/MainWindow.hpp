#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class Actions;
class Renderer;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
    
    void setRenderer(Renderer* renderer);
    
    void buildMenuAndToolBar(const Actions& actions);
    
    ~MainWindow();

private:
    Ui::MainWindow* ui;
};

#endif // GUI_MAINWINDOW_HPP
