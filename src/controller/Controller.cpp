#include "Controller.hpp"
#include "src/gui/MainWindow.hpp"
#include "src/model/Model.hpp"
#include "src/renderer/Renderer.hpp"

#include <algorithm>
#include <QAction>
#include <QSettings>

const QString Controller::DIFFICULTY_GROUP = "difficulty";
const QString Controller::LEVEL_KEY = "level";
const QString Controller::ROWS_KEY = "rows";
const QString Controller::COLUMNS_KEY = "columns";
const QString Controller::MINES_KEY = "mines";

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

Controller::Controller(Model* const model, MainWindow* const mainWindow, Renderer* const renderer) :
        model(model),
        mainWindow(mainWindow),
        renderer(renderer),
        randGenerator(QRandomGenerator::securelySeeded()) {
    renderer->setModel(model);
    mainWindow->setRenderer(renderer);
    QObject::connect(actions.newGame, &QAction::triggered, this, &Controller::newGame);
}

void Controller::start() {
    readPreviousBoardLevel();
    mainWindow->buildMenuAndToolBar(actions);
    mainWindow->show();
}

void Controller::readPreviousBoardLevel() const {
    QSettings settings;
    settings.beginGroup(DIFFICULTY_GROUP);
    ksaper::Size size;
    ksaper::Level level = static_cast<ksaper::Level>(settings.value(LEVEL_KEY, ksaper::EASY).toInt());
    
    if(ksaper::LevelToSize.keys().contains(level))
        size = ksaper::LevelToSize[level];
    else {
        const auto defaultLevel = ksaper::LevelToSize[ksaper::DEFAULT_LEVEL];
        const auto rows = settings.value(ROWS_KEY, defaultLevel.dimension.rows).toInt();
        const auto columns = settings.value(COLUMNS_KEY, defaultLevel.dimension.columns).toInt();
        const auto mines = settings.value(MINES_KEY, defaultLevel.mines).toInt();
        size = {{rows, columns}, mines};
    }
    settings.endGroup();
    
    model->setLevel(level, size);
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
