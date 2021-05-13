#ifndef RENDERER_NULLRENDERER_HPP
#define RENDERER_NULLRENDERER_HPP

#include "IRenderer.hpp"

class NullRenderer : public IRenderer {
public:
    static IRenderer& instance() { return renderer; }
    
    NullRenderer(const NullRenderer& object) = delete;

private:
    static NullRenderer renderer;

private:
    NullRenderer() = default;

public:
    void render(QPainter& painter) Q_DECL_OVERRIDE {}
};

#endif // RENDERER_NULLRENDERER_HPP
