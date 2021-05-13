#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include "IRenderer.hpp"
#include "src/model/NullModel.hpp"

#include <QPainter>

class IModel;

class Renderer : public IRenderer {
public:
    void setModel(const IModel* model);
    
    void render(QPainter& painter) Q_DECL_OVERRIDE;

private:
    int spacingSize(int width, int height);
    
    int fieldSize(int width, int height, int spacing);

private:
    const IModel* model = &NullModel::instance();
};

#endif // RENDERER_RENDERER_HPP
