#ifndef RENDERER_IRENDERER_HPP
#define RENDERER_IRENDERER_HPP

#include <QPainter>

class IRenderer {
public:
    virtual void render(QPainter& painter) = 0;
};

#endif // RENDERER_IRENDERER_HPP
