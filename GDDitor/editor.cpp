#include "editor.hpp"

#include "document.hpp"
#include "settings.hpp"
#include "utils.hpp"

using namespace Settings;

Editor::Editor()
{
    Init();
}

QWidget* Editor::GetWindow()
{
    return &window;
}

void Editor::Init()
{
    // mode
    mode = e_EditorMode::None;

    // window
    //palette.setColor(QPalette::Window, Qt::red);
    //window.setPalette(palette);
    window.setGeometry(0, 30, c_windowSizeX, c_windowSizeY);
    window.show();

    // buttons
    nodeButton.Init(&window,
                    c_inspectorPosX,
                    c_inspectorPosY,
                    c_inspectorSizeX,
                    60);

    // fileds
    posFieldX.Init(&window, c_inspectorPosX, 100, 50, 30, "x");
    connect(&posFieldX, SIGNAL(validated()), this, SLOT(UpdateSelectionPosition()));
    posFieldY.Init(&window, c_inspectorPosX + c_margin + 100, 100, 50, 30, "y");
    connect(&posFieldY, SIGNAL(validated()), this, SLOT(UpdateSelectionPosition()));
}

void Editor::Open(Document* _document)
{
    // give the document reference to editor
    currentDocument = _document;

    // give the editor reference to document
    _document->Link(this);

    // link editor button to document
    QObject::connect(&nodeButton, SIGNAL(clicked()), currentDocument, SLOT(AddNode()));
}

void Editor::UpdateSelectionPosition()
{
    vec2<int> newPos;
    newPos.x = posFieldX.GetText().toInt();
    newPos.y = posFieldY.GetText().toInt();

    selection->SetPos(newPos.x, newPos.y);
}

void Editor::EmptySelection()
{
    selection = nullptr;

    // hide contexual inspector
    posFieldX.hide();
    posFieldY.hide();
}

void Editor::SetSelection(Node* _node)
{
    selection = _node;

    // set contextual inspector to selection values
    posFieldX.SetText(QString::number(selection->GetPos().x));
    posFieldY.SetText(QString::number(selection->GetPos().y));

    // show contextual inspector
    posFieldX.show();
    posFieldY.show();
}
