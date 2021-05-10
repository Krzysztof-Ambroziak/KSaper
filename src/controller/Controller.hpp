#ifndef CONTROLLER_CONTROLLER_HPP
#define CONTROLLER_CONTROLLER_HPP

#include "src/Definitions.hpp"
#include "src/gui/Actions.hpp"

#include <QObject>
#include <QRandomGenerator>
#include <QVector>

class MainWindow;
class Model;

class Controller : public QObject {
private:
    static int mineSquares(const QVector<ksaper::Field>& fields);
    
    static int emptySquares(const QVector<ksaper::Field>& fields);
    
    static void specialCopy(const QVector<ksaper::Field>& from, QVector<ksaper::Field>& to);

public:
    Controller(Model* model, MainWindow* mainWindow);
    
    void start();

private:
    bool isMinesFullFilled(const QVector<ksaper::Field>& squares) const;

private slots:
    void newGame();

private:
    Model* const model;
    
    MainWindow* const mainWindow;
    
    Actions actions;
    
    QRandomGenerator randGenerator;
};

#endif // CONTROLLER_CONTROLLER_HPP
