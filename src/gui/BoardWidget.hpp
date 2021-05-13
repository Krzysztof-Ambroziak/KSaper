#ifndef GUI_BOARDWIDGET_HPP
#define GUI_BOARDWIDGET_HPP

#include <QWidget>

class Renderer;

class BoardWidget : public QWidget {
public:
    static constexpr int PADDING = 20;
    static constexpr int MIN_SIZE = 10;
    static constexpr int MIN_SPACING = 1;

public:
    explicit BoardWidget(QWidget* parent = nullptr);
    
    void setRenderer(Renderer* renderer);

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;

private:
    Renderer* renderer = nullptr;
};

#endif // GUI_BOARDWIDGET_HPP
