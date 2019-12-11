#include "document.hpp"

#include "editor.hpp"
#include "settings.hpp"

using namespace Settings;

Document::Document()
    : QObject()
{
    // background color
    QPalette palette;
    QColor softYellow(255, 217, 179);
    palette.setColor(QPalette::Window, softYellow);
    window.setPalette(palette);
    window.setAutoFillBackground(true);

    // size and pos
    window.setGeometry(c_margin, c_margin, c_documentSizeX, c_documentSizeY);

    // hide window cause it is not link to the editor for now
    window.hide();

    // connect window clicked signal to unselect current selection
    connect(&window, SIGNAL(clicked()), this, SLOT(EmptySelection()));
}

Document::~Document()
{
    for (auto& node : nodes)
    {
        if (node != nullptr)
        {
            delete(node);
        }
    }

    nodes.clear();
}

void Document::AddNode()
{
    Node* newNode = new Node(&window);
    newNode->Init(this);

    nodes.push_back(newNode);
}

void Document::Link(Editor* _editor)
{
    // ref on editor
    editor = _editor;

    // insert document window into editor window
    window.setParent(_editor->GetWindow());

    // show document
    window.show();
}

void Document::EmptySelection()
{
    // if something is selected
    if (selection != nullptr)
    {
        // set the selected object to a not selected state
        selection->SetUnselected();

        // set selection to null
        selection = nullptr;

        // transmite unselection to editor
        editor->EmptySelection();
    }
}

void Document::SetSelection(Node* _node)
{
    EmptySelection();

    // set new selected object to a selected state
    _node->SetSelected();

    // select to new selected object
    selection = _node;

    // transmite selection to editor
    editor->SetSelection(_node);
}
