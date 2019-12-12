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
    QString name;
    QVector<Node*> nodes{};
    Node* selection{};

    e_DocumentMode mode;

public:
    ClickableWidget window;
    Editor* editor;

    void Reset();

    Document();
    ~Document();

public slots:
    void Save(QString _directory); // load and save
    void Load(QString _path);
    void Link(Editor* _editor);
    void AddNode(int _x = 0, int _y = 0, QString _tittle = "Node");
    void EmptySelection();
    void SetSelection(Node* _node);
};
