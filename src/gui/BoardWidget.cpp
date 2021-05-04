#include "BoardWidget.hpp"

#include <QPainter>
#include <QPaintEvent>

BoardWidget::BoardWidget(QWidget* parent) :
        QWidget(parent) {
    const int minWidth = MAX_COLUMNS * (MIN_SIZE + MIN_SPACING) + MIN_SPACING + 2 * PADDING;
    const int minHeight = MAX_ROWS * (MIN_SIZE + MIN_SPACING) + MIN_SPACING + 2 * PADDING;
    
    setMinimumSize(minWidth, minHeight);
}

int BoardWidget::spacingSize() const {
    static constexpr int MIN_SIZE_SPACING = MIN_SIZE + MIN_SPACING;
    int spacing = 1;
    if((width()  >= 2 * (PADDING + MAX_COLUMNS * MIN_SIZE_SPACING + MIN_SPACING)) &&
            (height() >= 2 * (PADDING + MAX_ROWS * MIN_SIZE_SPACING + MIN_SPACING)))
        spacing += 1;
    
    return spacing;
}

int BoardWidget::fieldSize(int spacing) const {
    const int w = (width() - ((2 * PADDING) + (MAX_COLUMNS + 1) * spacing)) / MAX_COLUMNS;
    const int h = (height() - ((2 * PADDING) + (MAX_ROWS + 1) * spacing)) / MAX_ROWS;
    int size = std::min(w, h);
    if(spacing == MIN_SPACING)
        size = std::min(size, 2 * MIN_SIZE);
    
    return size;
}

void BoardWidget::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event)
    static QPainter painter;
    const int spacing = spacingSize();
    const int field = fieldSize(spacing);
    const int sizeAndSpacing = field + spacing;
    const int BOARD_WIDTH = MAX_COLUMNS * sizeAndSpacing + spacing;
    const int BOARD_HEIGHT = MAX_ROWS * sizeAndSpacing + spacing;
    const int x0 = (width() - BOARD_WIDTH) / 2;
    const int y0 = (height() - BOARD_HEIGHT) / 2;
    
    painter.begin(this);
    painter.fillRect(0, 0, width(), height(), Qt::gray);
    
    painter.fillRect(x0, y0, BOARD_WIDTH, BOARD_HEIGHT, Qt::white);
    
    for(int row = 0, size = sizeAndSpacing; row < MAX_ROWS; ++row)
        for(int col = 0; col < MAX_COLUMNS; ++col)
            painter.fillRect(x0 + col * size + spacing,
                             y0 + row * size + spacing,
                             field,
                             field,
                             Qt::lightGray);
    painter.end();
}
