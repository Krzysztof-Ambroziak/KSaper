#ifndef MODEL_IMODEL_HPP
#define MODEL_IMODEL_HPP

#include "src/Definitions.hpp"

#include <QSize>

class IModel {
public:
    virtual int rows() const = 0;
    
    virtual int columns() const = 0;
    
    virtual int mines() const = 0;
    
    virtual ksaper::Visibility visibility(int row, int column) const = 0;
    
    virtual ksaper::Neighbours neighbours(int row, int column) const = 0;
    
    virtual ksaper::Field field(int row, int column) const = 0;
    
    virtual QSize boardSize() const = 0;
};

#endif // MODEL_IMODEL_HPP
