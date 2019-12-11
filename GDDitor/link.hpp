#pragma once

#include <QLabel>

class Link : public QLabel
{
    Q_OBJECT

private:
    QString url{};

public:
    Link() = default;
    Link(QString _str);

public slots:
    void OpenUrl();
};
