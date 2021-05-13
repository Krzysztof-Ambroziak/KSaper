#include "Renderer.hpp"
#include "src/gui/BoardWidget.hpp"
#include "src/model/IModel.hpp"

void Renderer::setModel(const IModel* const model) {
    Renderer::model = model;
}

void Renderer::render(QPainter& painter) {
    const int width = painter.device()->width();
    const int height = painter.device()->height();
    const int spacing = spacingSize(width, height);
    const int field = fieldSize(width, height, spacing);
    const int sizeAndSpacing = field + spacing;
    const int boardWidth = model->columns() * sizeAndSpacing + spacing;
    const int boardHeight = model->rows() * sizeAndSpacing + spacing;
    const int x0 = (width - boardWidth) / 2;
    const int y0 = (height - boardHeight) / 2;
    
    painter.fillRect(0, 0, width, height, Qt::gray);
    painter.fillRect(x0, y0, boardWidth, boardHeight, Qt::white);
    
    for(int row = 0, size = sizeAndSpacing; row < model->rows(); row++)
        for(int col = 0; col < model->columns(); col++)
            painter.fillRect(x0 + col * size + spacing,
                             y0 + row * size + spacing,
                             field,
                             field,
                             Qt::lightGray);
}

int Renderer::spacingSize(int width, int height) {
    static constexpr int MIN_SIZE_SPACING = BoardWidget::MIN_SIZE + BoardWidget::MIN_SPACING;
    int spacing = 1;
    if((width >= 2 * (BoardWidget::PADDING + model->columns() * MIN_SIZE_SPACING + BoardWidget::MIN_SPACING)) &&
            (height >= 2 * (BoardWidget::PADDING + model->rows() * MIN_SIZE_SPACING + BoardWidget::MIN_SPACING)))
        spacing += 1;
    
    return spacing;
}

int Renderer::fieldSize(int width, int height, int spacing) {
    const int w = (width - ((2 * BoardWidget::PADDING) + (model->columns() + 1) * spacing)) / model->columns();
    const int h = (height - ((2 * BoardWidget::PADDING) + (model->rows() + 1) * spacing)) / model->rows();
    int size = std::min(w, h);
    if(spacing == BoardWidget::MIN_SPACING)
        size = std::min(size, 2 * BoardWidget::MIN_SIZE);
    
    return size;
}
