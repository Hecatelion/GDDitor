#include "node.hpp"

#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include "document.hpp"

Node::Node()
    : QLabel()
{
    // palette
    palette.setColor(QPalette::Window, Qt::blue);
    palette.setColor(QPalette::WindowText, Qt::black);
    setPalette(palette);
    setAutoFillBackground(true);

    // font
    font = QFont("Arial", 14, QFont::Thin);
    setFont(font);
}

Node::Node(QWidget* _parent)
    : QLabel(_parent)
{ }

void Node::paintEvent(QPaintEvent* _event)
{
    // painter draws shapes onto widget
    QPainter painter(this);

    // brush fills the shape
    painter.setBrush(Qt::NoBrush);

    // pen draws the outline of shape
    QPen pen;
    pen.setWidth(10);

    if (isSelected)
    {
        // node selected -> red outline
        pen.setColor(Qt::red);
        painter.setPen(pen);
    }
    else
    {
        // node not selected -> black outline
        pen.setColor(Qt::black);
        painter.setPen(pen);
    }

    // draw ellipse
    painter.drawEllipse(10, 10, 80, 80);
}

void Node::mousePressEvent(QMouseEvent* _mouseEvent)
{
    if (_mouseEvent->buttons() == Qt::LeftButton)
    {
        document->SetSelection(this);
    }
}

vec2<int> Node::GetPos()
{
    vec2<int> position(pos().x(), pos().y());
    return position;
}
void Node::SetPos(int _x, int _y)
{
    int w = QLabel::size().width();
    int h = QLabel::size().height();

    QLabel::setGeometry(_x, _y, w, h);

    QLabel::setText("Truc");
    qDebug() << QLabel::text();
}

vec2<int> Node::GetSize()
{
    vec2<int> pos(size().width(), size().height());
    return pos;
}
void Node::SetSize(int _w, int _h)
{
    int x = QLabel::pos().x();
    int y = QLabel::pos().y();

    QLabel::setGeometry(x, y, _w, _h);
}

void Node::Draw()
{
    update();
    QLabel::show();
}

void Node::Init(Document* _document)
{
    static bool isFirst = true;
    document = _document;

    if (isFirst)
    {
        SetPos(250, 300);
        isFirst = false;
    }
    else
    {
        SetPos(400, 300);
    }

    SetSize(100, 100);

    setText("Node");

    Draw();
}

void Node::SetSelected()
{
    isSelected = true;
    //document->SetSelection(this);
    Draw();
}

void Node::SetUnselected()
{
    isSelected = false;
    Draw();
}
