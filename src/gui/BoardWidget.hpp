#ifndef GUI_BOARDWIDGET_HPP
#define GUI_BOARDWIDGET_HPP

#include "src/renderer/NullRenderer.hpp"

#include <QWidget>

class IRenderer;

class BoardWidget : public QWidget {
    Q_OBJECT

public:
    static constexpr int PADDING = 20;
    static constexpr int MIN_SIZE = 10;
    static constexpr int MIN_SPACING = 1;

public:
    explicit BoardWidget(QWidget* parent = nullptr);
    
    void setRenderer(IRenderer* renderer);

protected:
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
    
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

signals:
    void clicked(const QPoint& point, Qt::MouseButton mouseButton);
    
    void resized(const QSize& size);

private:
    IRenderer* renderer = &NullRenderer::instance();
};

#endif // GUI_BOARDWIDGET_HPP
