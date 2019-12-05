#pragma once

#include <QObject>
#include <QVector>

#include "clickable_widget.hpp"
#include "node.hpp"


enum class e_DocumentMode
{
    ReadOnly,
    Edit
};


class Editor;

class Document : public QObject
{
    Q_OBJECT

private:
    QPalette palette;

    QVector<Node*> nodes{};
    Node* selection{};

    e_DocumentMode mode;

public:
    ClickableWidget window;
    Editor* editor;

    Document();
    ~Document();

public slots:
    void Link(Editor* _editor);
    void AddNode();
    void EmptySelection();
    void SetSelection(Node* node);
};
