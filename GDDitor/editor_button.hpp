#pragma once

#include <QPushButton>

class EditorButton : public QPushButton
{
    Q_OBJECT

public:
    EditorButton() = default;
    //EditorButton(QWidget* _window, int _x, int _y);

    void Init(QWidget* _window, int _x, int _y, int _w, int _h, QString _str);
};
