#ifndef MODEL_IMODEL_HPP
#define MODEL_IMODEL_HPP

#include "src/Definitions.hpp"

class IModel {
public:
    virtual int rows() const = 0;
    
    virtual int columns() const = 0;
    
    virtual int mines() const = 0;
    
    virtual ksaper::Field field(int row, int column) const = 0;
};

#endif // MODEL_IMODEL_HPP
