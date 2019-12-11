#include "link.hpp"
#include <QDesktopServices>
#include <QUrl>


Link::Link(QString _str)
{
    url = _str;
}

void Link::OpenUrl()
{
   QDesktopServices::openUrl(QUrl(url));
}
