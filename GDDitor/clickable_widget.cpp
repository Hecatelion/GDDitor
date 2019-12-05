#include "clickable_widget.hpp"

#include <QMouseEvent>

void ClickableWidget::mousePressEvent(QMouseEvent* _mouseEvent)
{
    if (_mouseEvent->buttons() == Qt::LeftButton)
    {
        emit clicked();
    }
}
