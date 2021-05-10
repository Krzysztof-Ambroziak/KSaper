#include "Model.hpp"

int Model::rows() const {
    return fBoard.rows();
}

int Model::columns() const {
    return fBoard.columns();
}

int Model::mines() const {
    return fBoard.mines();
}

ksaper::Field Model::field(int row, int column) const {
    return fBoard.square(row, column).field;
}

void Model::setSquare(int row, int column, const ksaper::Square& square) {
    fBoard.setSquare(row, column, square);
}
