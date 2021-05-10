#ifndef MODEL_MODEL_HPP
#define MODEL_MODEL_HPP

#include "Board.hpp"

class Model {
public:
    int rows() const;
    
    int columns() const;
    
    int mines() const;
    
    ksaper::Field field(int row, int column) const;
    
    void setSquare(int row, int column, const ksaper::Square& square);

private:
    Board fBoard = Board::easyBoard();
};

#endif // MODEL_MODEL_HPP
