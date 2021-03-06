#include "editor.hpp"

#include <QFileDialog>

#include "document.hpp"
#include "settings.hpp"
#include "utils.hpp"

using namespace Settings;

Editor::Editor()
{
    Init();
    OpenNewDocument();
}

Editor::~Editor()
{
    DeleteCurrentDocument();
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
    nodeButton.Init(&window, c_inspectorPosX, c_inspectorPosY, c_inspectorSizeX, 60, "Add Node");
    QObject::connect(&nodeButton, SIGNAL(clicked()), this, SLOT(AddNodeToDocument()));

    saveDocumentButton.Init(&window, c_margin, c_margin, 60, c_toolbarSizeY, "Save");
    QObject::connect(&saveDocumentButton, SIGNAL(clicked()), this, SLOT(SaveDocument()));

    loadDocumentButton.Init(&window, 60 + 2 * c_margin, c_margin, 60, c_toolbarSizeY, "Load");
    QObject::connect(&loadDocumentButton, SIGNAL(clicked()), this, SLOT(LoadDocument()));

    // properies
        // document name
    documentNameProperty.Init(&window,
                         c_inspectorPosX - 300 - c_margin, c_margin,
                         300, c_propertySizeY,
                         0.5f,
                         "document name");

    connect(&documentNameProperty, SIGNAL(validated()), this, SLOT(UpdateDocumentName()));

        // pos X
    posXProperty.Init(&window,
                      c_inspectorPosX, c_propertyPosY,
                      (c_inspectorSizeX - c_margin) / 2, c_propertySizeY,
                      0.4f,
                      "x");

    connect(&posXProperty, SIGNAL(validated()), this, SLOT(UpdateSelectionPosition()));

        // pos Y
    posYProperty.Init(&window,
                      c_inspectorPosX + posXProperty.size().width() + c_margin, c_propertyPosY,
                      (c_inspectorSizeX - c_margin) / 2, c_propertySizeY,
                      0.4f,
                      "y");

    connect(&posYProperty, SIGNAL(validated()), this, SLOT(UpdateSelectionPosition()));

        // tittle
    tittleProperty.Init(&window,
                        c_inspectorPosX, c_propertyPosY + c_propertySizeY + c_margin,
                        c_inspectorSizeX, c_propertySizeY,
                        0.3f,
                        "Tittle");

    connect(&tittleProperty, SIGNAL(validated()), this, SLOT(UpdateSelectionTittle()));

    // document
    currentDocument = nullptr;
}

void Editor::Open(Document* _document)
{
    // give the document reference to editor
    currentDocument = _document;

    // init document name property
    documentNameProperty.SetFieldContent(currentDocument->GetName());
    documentNameProperty.show();

    // give the editor reference to document
    _document->Link(this);
}

// ------------------------------------
//          document actions
// ------------------------------------

void Editor::UpdateDocumentName()
{
    currentDocument->SetName(documentNameProperty.GetFieldContent());
}

void Editor::AddNodeToDocument()
{
    currentDocument->AddNode();
}

void Editor::SaveDocument()
{
    QString dir = "saves/"; // file explorer
    currentDocument->Save(dir);
}

void Editor::LoadDocument() // json read
{
    // delete current doc to avoid memory leaks
    DeleteCurrentDocument();

    //QString path = "saves/doc1.gdd"; // file explorer
    QString path = QFileDialog::getOpenFileName(nullptr, tr("Document Selection"), "saves/", tr("File (*.gdd)"));

    Document* loadedDoc = new Document();
    loadedDoc->Load(path);

    // link loaded document in editor
    Open(loadedDoc);
}

void Editor::OpenNewDocument()
{
    // delete current doc to avoid memory leaks
    DeleteCurrentDocument();

    Document* blankDoc = new Document();

    Open(blankDoc);
}

void Editor::DeleteCurrentDocument()
{
    if (currentDocument != nullptr)
    {
        delete (currentDocument);
    }
}

// ------------------------------------
//          selection actions
// ------------------------------------

void Editor::UpdateSelectionPosition()
{
    vec2<int> newPos;
    newPos.x = posXProperty.GetFieldContent().toInt();
    newPos.y = posYProperty.GetFieldContent().toInt();

    selection->SetPos(newPos.x, newPos.y);
}

void Editor::UpdateSelectionTittle()
{
    selection->SetTittle(tittleProperty.GetFieldContent());
}

void Editor::EmptySelection()
{
    selection = nullptr;

    // hide contexual inspector
    posXProperty.hide();
    posYProperty.hide();
    tittleProperty.hide();
}

void Editor::SetSelection(Node* _node)
{
    selection = _node;

    // set contextual inspector to selection's values
    posXProperty.SetFieldContent(QString::number(selection->GetPos().x));
    posYProperty.SetFieldContent(QString::number(selection->GetPos().y));
    tittleProperty.SetFieldContent(selection->GetTittle());

    // show contextual inspector
    posXProperty.show();
    posYProperty.show();
    tittleProperty.show();
}
