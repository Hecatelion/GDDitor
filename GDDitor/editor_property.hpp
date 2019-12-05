#pragma once

#include <QWidget>
#include <QLabel>
#include <QString>
#include "custom_text_field.hpp"


class EditorProperty : public QWidget
{
    Q_OBJECT

private:
    QLabel label;
    CustomTextField field;

public:
    using QWidget::QWidget;

    void Init(QWidget* _parent, int _x, int _y, int _w, int _h, float _ratio, QString _text);

    QString GetFieldContent();
    void SetFieldContent(QString _str);

signals:
    void validated();

public slots:
    void PropagateSignalValitated();
};
