#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <QPainter>

class IModel;

class Renderer {
public:
    void setModel(const IModel* model);
    
    void render(QPainter& painter);

private:
    int spacingSize(int width, int height);
    
    int fieldSize(int width, int height, int spacing);

private:
    const IModel* model = nullptr;
};

#endif // RENDERER_RENDERER_HPP
