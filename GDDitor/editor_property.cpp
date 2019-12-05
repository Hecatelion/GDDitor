#include "editor_property.hpp"
#include "settings.hpp"

using namespace Settings;

void EditorProperty::Init(QWidget* _parent, int _x, int _y, int _w, int _h, float _ratio, QString _text)
{
    // init property's widget
    this->setParent(_parent);
    this->setGeometry(_x, _y, _w, _h);
    this->hide();

    // init label
    label.setParent(this);

    int labelW = (int)(_w * _ratio) - c_margin / 2;
    label.setGeometry(0, 0, labelW, _h);

    label.setFont(QFont("Arial", 14, QFont::Thin));
    label.setAlignment(Qt::AlignCenter);
    label.setText(_text);

    label.setPalette(QPalette(QPalette::Window, Qt::red));
    label.setAutoFillBackground(false);

    label.show();

    // init field
    int fieldW = _w - (labelW + c_margin);
    field.Init(this, labelW + c_margin, 0, fieldW, _h, "<value>");
    field.show();

    // propagate field.validated() signal
    // when field emit validated(), property emit validate() too
    connect(&field, SIGNAL(validated()), this, SLOT(PropagateSignalValitated()));
}

QString EditorProperty::GetFieldContent()
{
    return field.GetText();
}

void EditorProperty::SetFieldContent(QString _str)
{
   field.SetText(_str);
}

void EditorProperty::PropagateSignalValitated()
{
    emit validated();
}
