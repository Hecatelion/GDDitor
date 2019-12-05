#pragma once

#include <QTextEdit>

class QWidget;

class CustomTextField : public QTextEdit
{
    Q_OBJECT
protected:
    void Validate();

public:
    CustomTextField() = default;
    void Init(QWidget* _parentWindow, int _x, int _y, int _w, int _h, QString _str);

    void keyPressEvent(QKeyEvent* _event) override;
    QString GetText();
    void SetText(QString _str);

signals:
    void validated();
    void validated(QString _str);
};
