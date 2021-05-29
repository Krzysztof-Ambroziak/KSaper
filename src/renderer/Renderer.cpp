#include "Renderer.hpp"
#include "src/gui/BoardWidget.hpp"
#include "src/model/IModel.hpp"

ksaper::Coordinate Renderer::coordinate(const QPoint& point) const {
    const int width = model->boardSize().width();
    const int height = model->boardSize().height();
    const int spacing = spacingSize(width, height);
    const int field = fieldSize(width, height, spacing);
    const int squareAugSize = field + spacing;
    const int boardWidth = model->columns() * squareAugSize + spacing;
    const int boardHeight = model->rows() * squareAugSize + spacing;
    const int offsetX = (width - boardWidth) / 2;
    const int offsetY = (height - boardHeight) / 2;
    const int px = point.x() - offsetX;
    const int py = point.y() - offsetY;
    const int column = px / squareAugSize;
    const int row = py / squareAugSize;
    ksaper::Coordinate coord{row, column};
    
    if(column >= model->columns() || px % squareAugSize < spacing)
        coord.column = -1;
    if(row >= model->rows() || py % squareAugSize < spacing)
        coord.row = -1;
    
    return coord;
}

void Renderer::setModel(const IModel* const model) {
    Renderer::model = model;
}

void Renderer::render(QPainter& painter) {
    const int width = model->boardSize().width();
    const int height = model->boardSize().height();
    const int spacing = spacingSize(width, height);
    const int field = fieldSize(width, height, spacing);
    const int sizeAndSpacing = field + spacing;
    const int boardWidth = model->columns() * sizeAndSpacing + spacing;
    const int boardHeight = model->rows() * sizeAndSpacing + spacing;
    const int offsetX = (width - boardWidth) / 2;
    const int offsetY = (height - boardHeight) / 2;
    
    painter.fillRect(0, 0, width, height, Qt::gray);
    painter.fillRect(offsetX, offsetY, boardWidth, boardHeight, Qt::white);
    
    for(int row = 0, size = sizeAndSpacing; row < model->rows(); row++)
        for(int col = 0; col < model->columns(); col++) {
            if(model->visibility(row, col) == ksaper::HIDDEN)
                painter.fillRect(offsetX + col * size + spacing,
                                 offsetY + row * size + spacing,
                                 field,
                                 field,
                                 Qt::lightGray);
            else {
                painter.drawPixmap(offsetX + col * size + spacing,
                                   offsetY + row * size + spacing,
                                   field,
                                   field,
                                   pixmaps[model->neighbours(row, col)]);
            }
        }
}

int Renderer::spacingSize(int width, int height) const {
    static constexpr int MIN_SIZE_SPACING = BoardWidget::MIN_SIZE + BoardWidget::MIN_SPACING;
    int spacing = 1;
    if((width >= 2 * (BoardWidget::PADDING + model->columns() * MIN_SIZE_SPACING + BoardWidget::MIN_SPACING)) &&
            (height >= 2 * (BoardWidget::PADDING + model->rows() * MIN_SIZE_SPACING + BoardWidget::MIN_SPACING)))
        spacing += 1;
    
    return spacing;
}

int Renderer::fieldSize(int width, int height, int spacing) const {
    const int w = (width - ((2 * BoardWidget::PADDING) + (model->columns() + 1) * spacing)) / model->columns();
    const int h = (height - ((2 * BoardWidget::PADDING) + (model->rows() + 1) * spacing)) / model->rows();
    int size = std::min(w, h);
    if(spacing == BoardWidget::MIN_SPACING)
        size = std::min(size, 2 * BoardWidget::MIN_SIZE);
    
    return size;
}
