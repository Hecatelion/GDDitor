#pragma once

#include <QObject>
#include <QLabel>
#include "editor_property.hpp"
#include "editor_button.hpp"
#include "custom_text_field.hpp"
#include "utils.hpp"
#include "document.hpp"

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
    Document* currentDocument;

    // window settings
    QPalette palette;
    QWidget window;

    // editor
    e_EditorMode mode;
    Node* selection;

    // buttons
    EditorButton newDocumentButton;
    EditorButton saveDocumentButton;
    EditorButton loadDocumentButton;
    EditorButton nodeButton;

    // properties
    EditorProperty posXProperty;
    EditorProperty posYProperty;
    EditorProperty tittleProperty;

public:
    Editor();
    ~Editor();
    void Init();

    QWidget* GetWindow();

    void Open(Document* _document);

    void EmptySelection();
    void SetSelection(Node* _node);

public slots:
    // document actions
    void DeleteCurrentDocument();
    void OpenNewDocument();
    void LoadDocument();
    void SaveDocument();
    void AddNodeToDocument();

    // selection actions
    void UpdateSelectionPosition();
    void UpdateSelectionTittle();
};
