#ifndef MODEL_NULLMODEL_HPP
#define MODEL_NULLMODEL_HPP

#include "IModel.hpp"

class NullModel : public IModel {
public:
    static IModel& instance() { return model; }

private:
    static NullModel model;

public:
    NullModel(const NullModel& object) = delete;
    
    int rows() const Q_DECL_OVERRIDE;
    
    int columns() const Q_DECL_OVERRIDE;
    
    int mines() const Q_DECL_OVERRIDE;
    
    ksaper::Field field(int row, int column) const Q_DECL_OVERRIDE;

    QSize boardSize() const Q_DECL_OVERRIDE;

private:
    NullModel() = default;
};

#endif // MODEL_NULLMODEL_HPP
