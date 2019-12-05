#pragma once

#include <QLabel>
#include <QString>

#include "utils.hpp"

class Document;

class Node : public QLabel
{
    Q_OBJECT

private:
    Document* document{};
    bool isSelected = false;

    QFont font;
    QPalette palette;

public:
    Node();
    Node(QWidget* _parent);

    void paintEvent(QPaintEvent* _event) override;
    void mousePressEvent(QMouseEvent* _mouseEvent) override;

    void Draw();
    void Init(Document* _document);

    vec2<int> GetPos();
    void SetPos(int _x, int _y);
    vec2<int> GetSize();
    void SetSize(int _w, int _h);

    void SetSelected();
    void SetUnselected();

signals:
    void selected();

};
