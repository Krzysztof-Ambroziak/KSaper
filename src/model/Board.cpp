#include "Board.hpp"

Board::Board(int rows, int columns, int mines) :
        fRows(rows > 0 && rows <= ksaper::MAX_ROWS ? rows : ksaper::MAX_ROWS),
        fColumns(columns > 0 && columns <= ksaper::MAX_COLUMNS ? columns : ksaper::MAX_COLUMNS),
        fMines(mines > 0 && mines < rows * columns ? mines : 1) {}

Board Board::easyBoard() {
    const ksaper::Size& size = ksaper::LevelToSize[ksaper::EASY];
    const ksaper::Dimension& dim = size.dimension;
    
    return Board(dim.rows, dim.columns, size.mines);
}

Board Board::advancedBoard() {
    const ksaper::Size& size = ksaper::LevelToSize[ksaper::ADVANCED];
    const ksaper::Dimension& dim = size.dimension;
    
    return Board(dim.rows, dim.columns, size.mines);
}

Board Board::expertBoard() {
    const ksaper::Size& size = ksaper::LevelToSize[ksaper::EXPERT];
    const ksaper::Dimension& dim = size.dimension;
    
    return Board(dim.rows, dim.columns, size.mines);
}

Board Board::customBoard(int r, int c, int m) {
    const int rows = r > 0 && r <= ksaper::MAX_ROWS ? r : ksaper::MAX_ROWS;
    const int columns = c > 0 && c <= ksaper::MAX_COLUMNS ? r : ksaper::MAX_COLUMNS;
    const int mines = m > 0 && m < rows * columns ? m : 1;
    
    return Board(rows, columns, mines);
}

int Board::rows() const {
    return fRows;
}

int Board::columns() const {
    return fColumns;
}

int Board::mines() const {
    return fMines;
}

void Board::setSquare(int row, int column, const ksaper::Square& square) {
    if(row >= 0 && row < fRows && column >= 0 && column < fColumns)
        fBoard[row][column] = square;
}

ksaper::Square Board::square(int row, int column) const {
    return fBoard[row][column];
}
