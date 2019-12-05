#include <QApplication>
#include <QDebug>
#include <QWidget>

#include "editor.hpp"
#include "document.hpp"
#include "utils.hpp"
#include "node.hpp"


using namespace std;

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    Editor editor;
    Document document;

    editor.Open(&document);

    app.exec();
    return 0;
}
