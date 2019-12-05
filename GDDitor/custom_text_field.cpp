#include "custom_text_field.hpp"

#include <QKeyEvent>
#include <QWidget>


void CustomTextField::Init(QWidget* _parentWindow, int _x, int _y, int _w, int _h, QString _str)
{
    setParent(_parentWindow);
    setGeometry(_x, _y, _w, _h);
    setText(_str);

    hide();
}

void CustomTextField::Validate()
{
    emit validated();
    //emit validated(getText());
}

void CustomTextField::keyPressEvent(QKeyEvent* _event)
{
    if (_event->key() == Qt::Key_Return)
    {
        Validate();
    }
    else
    {
        QTextEdit::keyPressEvent(_event);
    }
}

QString CustomTextField::GetText()
{
    return QTextEdit::toPlainText();
}
void CustomTextField::SetText(QString _str)
{
    QTextEdit::setText(_str);
}
