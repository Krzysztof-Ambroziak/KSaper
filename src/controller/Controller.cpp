#include "Controller.hpp"
#include "src/gui/MainWindow.hpp"
#include "src/gui/BoardWidget.hpp"
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
    QObject::connect(mainWindow->boardWidget(), &BoardWidget::clicked, this, &Controller::clicked);
    QObject::connect(mainWindow->boardWidget(), &BoardWidget::resized, this->model, &Model::setBoardSize);
}

void Controller::start() {
    readPreviousBoardLevel();
    mainWindow->buildMenuAndToolBar(actions);
    newGame();
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

void Controller::leftButtonClicked(const ksaper::Coordinate& coords) {
    const int row = coords.row;
    const int column = coords.column;
    if(model->visibility(row, column) == ksaper::HIDDEN && model->mark(row, column) == ksaper::NO_MARK)
        uncoverGroup(coords);
    mainWindow->boardWidget()->repaint();
}

QVector<ksaper::Neighbours> Controller::computeNeighbours(const QVector<ksaper::Field>& fields) const {
    const auto rows = model->rows();
    const auto columns = model->columns();
    QVector<ksaper::Neighbours> neighbours(rows * columns, ksaper::ZERO);
    
    for(int row = 0; row < rows; row++)
        for(int column = 0; column < columns; column++) {
            const int position = row * columns + column;
            int n = 0;
            
            // Clockwise checking fields starting from top-left square
            if(row > 0 && column > 0 && fields[position - columns - 1] == ksaper::MINE) n++;
            if(row > 0 && fields[position - columns] == ksaper::MINE) n++;
            if(row > 0 && column < columns - 1 && fields[position - columns + 1] == ksaper::MINE) n++;
            if(column > 0 && fields[position - 1] == ksaper::MINE) n++;
            if(column < columns - 1 && fields[position + 1] == ksaper::MINE) n++;
            if(row < rows - 1 && column > 0 && fields[position + columns - 1] == ksaper::MINE) n++;
            if(row < rows - 1 && fields[position + columns] == ksaper::MINE) n++;
            if(row < rows - 1 && column < columns - 1 && fields[position + columns + 1] == ksaper::MINE) n++;
            
            neighbours[position] = static_cast<ksaper::Neighbours>(n);
        }
    
    return neighbours;
}

void Controller::uncoverGroup(const ksaper::Coordinate& coordinate) const {
    enum Color {
        WHITE, GREY, BLACK
    };
    QVector<Color> visited(model->rows() * model->columns(), Color::WHITE);
    
    QVector<ksaper::Coordinate> squares;
    if(model->field(coordinate.row, coordinate.column) == ksaper::EMPTY && model->neighbours(coordinate.row, coordinate.column) == ksaper::ZERO)
        squares.push_back({coordinate.row, coordinate.column});
    model->setVisible(coordinate.row, coordinate.column);
    
    while(!squares.isEmpty())
    {
        int r;
        int c;
        ksaper::Coordinate coords = squares.takeFirst();
        
        r = coords.row - 1;
        c = coords.column - 1;
        if(r >= 0 && c >= 0) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row - 1;
        c = coords.column;
        if(r >= 0) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row - 1;
        c = coords.column + 1;
        if(r >= 0 && c < model->columns()) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row;
        c = coords.column - 1;
        if(c >= 0) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row;
        c = coords.column + 1;
        if(c < model->columns()) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row + 1;
        c = coords.column - 1;
        if(r < model->rows() && c >= 0) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row + 1;
        c = coords.column;
        if(r < model->rows()) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        r = coords.row + 1;
        c = coords.column + 1;
        if(r < model->rows() && c < model->columns()) {
            model->setVisible(r, c);
            if(model->field(r, c) == ksaper::EMPTY && model->neighbours(r, c) == ksaper::ZERO && visited[r * model->columns() + c] == Color::WHITE) {
                squares.push_back({r, c});
                visited[r * model->columns() + c] = Color::GREY;
            }
        }
        
        visited[coords.row * model->columns() + coords.column] = Color::BLACK;
    }
}

void Controller::clicked(const QPoint& point, Qt::MouseButton button) {
    auto coords = renderer->coordinate(point);
    
    switch(button) {
    case Qt::LeftButton:
        leftButtonClicked(coords);
        break;
    }
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
    
    QVector<ksaper::Neighbours> neighbours = computeNeighbours(squares);
    
    for(int row = 0; row < rows; row++)
        for(int column = 0; column < columns; column++)
            model->setSquare(row, column, {ksaper::Visibility::HIDDEN,
                                           squares[row * columns + column],
                                           neighbours[row * columns + column],
                                           ksaper::NO_MARK}
                             );
    mainWindow->boardWidget()->repaint();
}
