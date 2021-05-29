#include "Model.hpp"

int Model::rows() const {
    return fBoard->rows();
}

int Model::columns() const {
    return fBoard->columns();
}

int Model::mines() const {
    return fBoard->mines();
}

ksaper::Field Model::field(int row, int column) const {
    return fBoard->square(row, column).field;
}

ksaper::Mark Model::mark(int row, int column) const {
    return fBoard->square(row, column).mark;
}

ksaper::Visibility Model::visibility(int row, int column) const {
    return fBoard->square(row, column).visibility;
}

ksaper::Neighbours Model::neighbours(int row, int column) const {
    return fBoard->square(row, column).neighbours;
}

void Model::setVisible(int row, int column) {
    auto square = fBoard->square(row, column);
    square.visibility = ksaper::VISIBLE;
    
    fBoard->setSquare(row, column, square);
}

QSize Model::boardSize() const {
    return fBoardSize;
}

void Model::setLevel(ksaper::Level level, const ksaper::Size& size) {
    fLevel = level;
    switch(level) {
    case ksaper::EASY:
        fBoard = std::make_unique<Board>(Board::easyBoard());
        break;
    case ksaper::ADVANCED:
        fBoard = std::make_unique<Board>(Board::advancedBoard());
        break;
    case ksaper::EXPERT:
        fBoard = std::make_unique<Board>(Board::expertBoard());
        break;
    case ksaper::CUSTOM:
        fBoard = std::make_unique<Board>(Board::customBoard(size.dimension.rows, size.dimension.columns, size.mines));
        break;
    default:
        fBoard = std::make_unique<Board>(Board::easyBoard());
    }
}

void Model::setSquare(int row, int column, const ksaper::Square& square) {
    fBoard->setSquare(row, column, square);
}

void Model::setBoardSize(const QSize& boardSize) {
    fBoardSize = boardSize;
}
