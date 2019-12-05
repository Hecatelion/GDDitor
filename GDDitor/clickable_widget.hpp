#pragma once

#include <QWidget>

class ClickableWidget : public QWidget
{
    Q_OBJECT

private:
    void mousePressEvent(QMouseEvent* _mouseEvent) override;

public:
    using QWidget::QWidget;

signals:
    void clicked();
};
