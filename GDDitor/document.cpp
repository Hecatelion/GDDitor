#include "document.hpp"

#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

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
    window.setGeometry(c_margin, c_toolbarSizeY + c_margin * 2, c_documentSizeX, c_documentSizeY);

    // hide window cause it is not link to the editor for now
    window.hide();

    // connect window clicked signal to unselect current selection
    connect(&window, SIGNAL(clicked()), this, SLOT(EmptySelection()));

    // init datas
    Reset();
}

Document::~Document()
{
    Reset();
}

void Document::Save(QString _dir) // json write
{
    QFile saveFile(_dir + name + ".gdd");

    // open file and check if it's valid
    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }

    // write values in the file
    QJsonObject json;
    json["name"] = name;

    // write each node values
    QJsonArray nodesJsonArr;
    for (const auto& n : nodes)
    {
        QJsonObject nodeJson;
        nodeJson["tittle"] = n->GetTittle();
        nodeJson["x"] = n->GetPos().x;
        nodeJson["y"] = n->GetPos().y;

        nodesJsonArr.append(nodeJson);
    }
    json["nodes"] = nodesJsonArr;

    // save as json file
    QJsonDocument jsonDoc(json);
    saveFile.write(jsonDoc.toJson());

    qDebug() << "doc saved! :3";
}

void Document::Load(QString _path)
{
    // clear document datas
    Reset();

    QFile loadFile(_path);

    // open file and check if it's valid
    if(!loadFile.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open file.");
        return;
    }

     QByteArray saveData = loadFile.readAll();
     QJsonDocument jsonDoc(QJsonDocument::fromJson(saveData));
     QJsonObject json = jsonDoc.object();

     // read values from file
     name = json["name"].toString();

     QJsonArray nodesArr = json["nodes"].toArray();

     for(const auto& n : nodesArr)
     {
         // read each node values stored in json file
         QJsonObject jsonNode(n.toObject());
         int x = jsonNode["x"].toInt();
         int y = jsonNode["y"].toInt();
         QString tittle = jsonNode["tittle"].toString();

         // add node following read datas
         AddNode(x, y, tittle);
     }

     qDebug() << name;
}

void Document::AddNode(int _x, int _y, QString _tittle)
{
    Node* newNode = new Node(&window);
    newNode->Init(this, _x, _y, _tittle);

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

void Document::Reset()
{
    // name
    SetName("no_name");

    // nodes
    for (auto& node : nodes)
    {
        if (node != nullptr)
        {
            delete(node);
        }
    }

    nodes.clear();
}

const QString Document::GetName()
{
    return name;
}

void Document::SetName(QString _name)
{
    name = _name;
}
