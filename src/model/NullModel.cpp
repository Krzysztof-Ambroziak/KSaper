#include "NullModel.hpp"

NullModel NullModel::model;

int NullModel::rows() const {
    return ksaper::LevelToSize[ksaper::DEFAULT_LEVEL].dimension.rows;
}

int NullModel::columns() const {
    return ksaper::LevelToSize[ksaper::DEFAULT_LEVEL].dimension.columns;
}

int NullModel::mines() const {
    return ksaper::LevelToSize[ksaper::DEFAULT_LEVEL].mines;
}

ksaper::Visibility NullModel::visibility(int row, int column) const {
    Q_UNUSED(row);
    Q_UNUSED(column);
    return ksaper::HIDDEN;
}

ksaper::Neighbours NullModel::neighbours(int row, int column) const {
    return ksaper::ZERO;
}

ksaper::Field NullModel::field(int row, int column) const {
    Q_UNUSED(row);
    Q_UNUSED(column);
    return ksaper::EMPTY;
}

QSize NullModel::boardSize() const {
    return {0, 0};
}
