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
    QLabel nameLabel;
    QVector<Node*> nodes{};
    Node* selection{};

    e_DocumentMode mode;

public:
    ClickableWidget window;
    Editor* editor;

    void SetName(QString _name);
    const QString GetName();
    void Reset();

    Document();
    ~Document();

public slots:
    void Save(QString _directory);
    void Load(QString _path);
    void Link(Editor* _editor);
    void AddNode(int _x = 0, int _y = 0, QString _tittle = "Node");
    void EmptySelection();
    void SetSelection(Node* _node);
};
