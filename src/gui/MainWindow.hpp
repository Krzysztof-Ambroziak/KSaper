#ifndef GUI_MAINWINDOW_HPP
#define GUI_MAINWINDOW_HPP

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class Actions;
class BoardWidget;
class IRenderer;

class MainWindow : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);
    
    BoardWidget* boardWidget() const;
    
    void setRenderer(IRenderer* renderer);
    
    void buildMenuAndToolBar(const Actions& actions);
    
    ~MainWindow();

private:
    Ui::MainWindow* ui;
};

#endif // GUI_MAINWINDOW_HPP
