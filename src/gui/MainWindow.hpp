#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
    
    ~MainWindow();

private:
    Ui::MainWindow* ui;
};

#endif // GUI_MAINWINDOW_HPP
