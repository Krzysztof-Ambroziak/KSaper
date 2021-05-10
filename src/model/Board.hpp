#ifndef MODEL_BOARD_HPP
#define MODEL_BOARD_HPP

#include "src/Definitions.hpp"

class Board {
public:
    static Board easyBoard();
    
    static Board advancedBoard();
    
    static Board expertBoard();
    
    static Board customBoard(int rows = ksaper::MAX_ROWS, int columns = ksaper::MAX_COLUMNS, int mines = 1);

public:
    int rows() const;
    
    int columns() const;
    
    int mines() const;
    
    void setSquare(int row, int column, const ksaper::Square& square);

    ksaper::Square square(int row, int column) const;

private:
    Board(int rows, int columns, int mines);

private:
    const int fRows;
    
    const int fColumns;
    
    const int fMines;
    
    std::array<std::array<ksaper::Square, ksaper::MAX_COLUMNS>, ksaper::MAX_ROWS> fBoard;
};

#endif // MODEL_BOARD_HPP
