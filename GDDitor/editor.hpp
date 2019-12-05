#pragma once

#include <QObject>
#include <QLabel>
#include "editor_property.hpp"
#include "editor_button.hpp"
#include "custom_text_field.hpp"
#include "utils.hpp"


enum class e_EditorMode
{
    None,
    EditNode
};

class Document;
class Node;

class Editor : public QObject
{
    Q_OBJECT

private:
    // opened document reference
    Document* currentDocument;

    // window settings
    QPalette palette;
    QWidget window;

    // editor
    e_EditorMode mode;
    Node* selection;

    // buttons
    EditorButton nodeButton;

    // properties
    EditorProperty posXProperty;
    EditorProperty posYProperty;
    EditorProperty tittleProperty;

public:
    Editor();
    void Init();

    QWidget* GetWindow();

    void Open(Document* _document);

    void EmptySelection();
    void SetSelection(Node* _node);

public slots:
    void UpdateSelectionPosition();
};
