#ifndef MODEL_MODEL_HPP
#define MODEL_MODEL_HPP

#include "Board.hpp"
#include "IModel.hpp"

#include <memory>

class Model : public IModel {
public:
    int rows() const Q_DECL_OVERRIDE;
    
    int columns() const Q_DECL_OVERRIDE;
    
    int mines() const Q_DECL_OVERRIDE;
    
    ksaper::Field field(int row, int column) const Q_DECL_OVERRIDE;
    
    void setLevel(ksaper::Level level, const ksaper::Size& size);
    
    void setSquare(int row, int column, const ksaper::Square& square);

private:
    ksaper::Level fLevel;
    
    std::unique_ptr<Board> fBoard = nullptr;
};

#endif // MODEL_MODEL_HPP
