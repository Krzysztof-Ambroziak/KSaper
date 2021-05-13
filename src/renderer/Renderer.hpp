#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <QPainter>

class Model;

class Renderer {
public:
    void setModel(const Model* model);
    
    void render(QPainter& painter);

private:
    int spacingSize(int width, int height);
    
    int fieldSize(int width, int height, int spacing);

private:
    const Model* model = nullptr;
};

#endif // RENDERER_RENDERER_HPP
