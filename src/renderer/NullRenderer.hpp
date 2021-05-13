#ifndef RENDERER_NULLRENDERER_HPP
#define RENDERER_NULLRENDERER_HPP

#include "IRenderer.hpp"

class NullRenderer : public IRenderer {
public:
    static IRenderer& instance() { return renderer; }

private:
    static NullRenderer renderer;

public:
    NullRenderer(const NullRenderer& object) = delete;
    
    void render(QPainter& painter) Q_DECL_OVERRIDE { Q_UNUSED(painter) }

private:
    NullRenderer() = default;
};

#endif // RENDERER_NULLRENDERER_HPP
