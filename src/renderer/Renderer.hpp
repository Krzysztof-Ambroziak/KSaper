#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include "IRenderer.hpp"
#include "src/Definitions.hpp"
#include "src/model/NullModel.hpp"

#include <QHash>

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
    
    const QHash<ksaper::Neighbours, QPixmap> pixmaps {
        {ksaper::ZERO, {}},
        {ksaper::ONE, {":/img/1"}},
        {ksaper::TWO, {":/img/2"}},
        {ksaper::THREE, {":/img/3"}},
        {ksaper::FOUR, {":/img/4"}},
        {ksaper::FIVE, {":/img/5"}},
        {ksaper::SIX, {":/img/6"}},
        {ksaper::SEVEN, {":/img/7"}},
        {ksaper::EIGHT, {":/img/8"}}
    };
};

#endif // RENDERER_RENDERER_HPP
