#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include "IRenderer.hpp"
#include "src/Definitions.hpp"
#include "src/model/NullModel.hpp"

#include <QPainter>

class IModel;
class QPoint;

class Renderer : public IRenderer {
public:
    ksaper::Coordinate coordinate(const QPoint& point) const;
    
    void setModel(const IModel* model);
    
    void render(QPainter& painter) Q_DECL_OVERRIDE;

private:
    int spacingSize(int width, int height) const;
    
    int fieldSize(int width, int height, int spacing) const;

private:
    const IModel* model = &NullModel::instance();
};

#endif // RENDERER_RENDERER_HPP
