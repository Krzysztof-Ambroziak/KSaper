#include "Controller.hpp"
#include "src/gui/MainWindow.hpp"
#include "src/model/Model.hpp"

#include <algorithm>

#include <QAction>

int Controller::mineSquares(const QVector<ksaper::Field>& squares) {
    return std::count(squares.cbegin(), squares.cend(), ksaper::MINE);
}

int Controller::emptySquares(const QVector<ksaper::Field>& squares) {
    return std::count(squares.cbegin(), squares.cend(), ksaper::EMPTY);
}

void Controller::specialCopy(const QVector<ksaper::Field>& from, QVector<ksaper::Field>& to) {
    for(int i = 0, j = 0; i < from.size(); i++, j++) {
        while(to[j] == ksaper::MINE)
            j++;
        if(from[i] == ksaper::MINE)
            to[j] = ksaper::MINE;
    }
}

Controller::Controller(Model* const model, MainWindow* const mainWindow) :
        model(model),
        mainWindow(mainWindow),
        randGenerator(QRandomGenerator::securelySeeded()) {
    QObject::connect(actions.newGame, &QAction::triggered, this, &Controller::newGame);
}

void Controller::start() {
    mainWindow->buildMenuAndToolBar(actions);
    
    mainWindow->show();
}

bool Controller::isMinesFullFilled(const QVector<ksaper::Field>& squares) const {
    return mineSquares(squares) == model->mines();
}

void Controller::newGame() {
    const auto rows = model->rows();
    const auto columns = model->columns();
    const auto fields = rows * columns;
    
    QVector<ksaper::Field> squares(fields, ksaper::EMPTY);
    while(!isMinesFullFilled(squares)) {
        int emptyCount = emptySquares(squares);
        QVector<ksaper::Field> buffer(emptyCount, ksaper::EMPTY);
        
        for(int i = mineSquares(squares); i < model->mines(); ++i)
            buffer[randGenerator.bounded(emptyCount)] = ksaper::MINE;
        specialCopy(buffer, squares);
    }
    
    for(int row = 0; row < rows; row++)
        for(int column = 0; column < columns; column++)
            model->setSquare(row, column, {squares[row * columns + column],
                                           ksaper::ZERO,
                                           ksaper::HIDDEN}
                             );
}
