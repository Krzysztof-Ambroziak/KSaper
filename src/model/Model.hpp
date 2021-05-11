#ifndef MODEL_MODEL_HPP
#define MODEL_MODEL_HPP

#include "Board.hpp"

#include <memory>

class Model {
public:
    int rows() const;
    
    int columns() const;
    
    int mines() const;
    
    ksaper::Field field(int row, int column) const;
    
    void setLevel(ksaper::Level level, const ksaper::Size& size);
    
    void setSquare(int row, int column, const ksaper::Square& square);

private:
    ksaper::Level fLevel;
    
    std::unique_ptr<Board> fBoard = nullptr;
};

#endif // MODEL_MODEL_HPP
