#include "BoardWidget.hpp"
#include "src/Definitions.hpp"
#include "src/renderer/Renderer.hpp"

#include <QPainter>

BoardWidget::BoardWidget(QWidget* parent) :
        QWidget(parent) {
    const int minWidth = ksaper::MAX_COLUMNS * (MIN_SIZE + MIN_SPACING) + MIN_SPACING + 2 * PADDING;
    const int minHeight = ksaper::MAX_ROWS * (MIN_SIZE + MIN_SPACING) + MIN_SPACING + 2 * PADDING;
    
    setMinimumSize(minWidth, minHeight);
}

void BoardWidget::setRenderer(IRenderer* const rend) {
    renderer = rend;
}

void BoardWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    static QPainter painter;
    
    painter.begin(this);
    renderer->render(painter);
    painter.end();
}
