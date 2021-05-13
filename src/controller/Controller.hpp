#ifndef CONTROLLER_CONTROLLER_HPP
#define CONTROLLER_CONTROLLER_HPP

#include "src/Definitions.hpp"
#include "src/gui/Actions.hpp"

#include <QObject>
#include <QRandomGenerator>
#include <QVector>

class MainWindow;
class Model;
class Renderer;

class Controller : public QObject {
private:
    static int mineSquares(const QVector<ksaper::Field>& fields);
    
    static int emptySquares(const QVector<ksaper::Field>& fields);
    
    static void specialCopy(const QVector<ksaper::Field>& from, QVector<ksaper::Field>& to);

private:
    static const QString DIFFICULTY_GROUP;
    
    static const QString LEVEL_KEY;
    static const QString ROWS_KEY;
    static const QString COLUMNS_KEY;
    static const QString MINES_KEY;

public:
    Controller(Model* model, MainWindow* mainWindow, Renderer* renderer);
    
    void start();

private:
    void readPreviousBoardLevel() const;
    
    bool isMinesFullFilled(const QVector<ksaper::Field>& squares) const;

private slots:
    void newGame();

private:
    Model* const model;
    
    MainWindow* const mainWindow;
    
    Renderer* const renderer;
    
    Actions actions;
    
    QRandomGenerator randGenerator;
};

#endif // CONTROLLER_CONTROLLER_HPP
