#include "editor_button.hpp"

#include <QWidget>

void EditorButton::Init(QWidget* _window, int _x, int _y, int _w, int _h)
{
    QPushButton::setParent(_window);
    setGeometry(_x, _y, _w, _h);
    setText("Add Node");

    show();
}
