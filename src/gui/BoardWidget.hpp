#ifndef GUI_BOARDWIDGET_HPP
#define GUI_BOARDWIDGET_HPP

#include <QWidget>

class BoardWidget : public QWidget {
private:
    static constexpr int PADDING = 20;
    static constexpr int MIN_SIZE = 10;
    static constexpr int MIN_SPACING = 1;

public:
    explicit BoardWidget(QWidget* parent = nullptr);
    
    int spacingSize() const;
    
    int fieldSize(int spacing) const;

protected:
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
};

#endif // GUI_BOARDWIDGET_HPP
