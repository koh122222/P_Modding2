#include "modifView.h"
#include "mainwindow.h"
#include <QDebug>
ModifView::ModifView(QWidget *parent) : QWidget(parent)
{
    testEditor = new QTextEdit(this);
    layout = new QGridLayout(this);
    allFilter = new QCheckBox("All",this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(allFilter,0,0);
    layout->addWidget(testEditor,1,0);

    connect(allFilter, SIGNAL(stateChanged(int)), this, SLOT(allPrint(int)));
}

void ModifView::localOpener()
{
    QString filePlace = static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceGame();
    filePlace+="/localisation";

    QVector <QString> files;

    allMap = new localMap;

    YAML::reedFile(filePlace+"/countries_l_english.yml",*allMap);
}

bool ModifView::messagePoint (QString localizedText)
{
    if (localizedText.size() > 0)
        if (  (localizedText[localizedText.size() - 1] == ".")
            ||(localizedText[localizedText.size() - 1] == "!")
            ||(localizedText[localizedText.size() - 1] == "?")
            ||(localizedText[localizedText.size() - 1] == ":"))
            return true;
    for (int i = 0; i <localizedText.size(); ++i)
    {
        if (localizedText[i] == "[")
            return false;
        if ((localizedText[i] == ".")
            ||(localizedText[i] == "!")
            ||(localizedText[i] == "?")
            ||(localizedText[i] == ":"))
            return true;
    }
    return false;
}

bool ModifView::tagPoint (QString programText)
{
    if (programText.size()==3)
        return true;
    return false;
}

bool ModifView::adj_tagPoint (QString programText)
{
    if (programText.size()==7)
        if (programText.mid(3,4) == "_ADJ")
            return true;
    return false;
}

void ModifView::allPrint(int a)
{
    testEditor->setText("");
    if (a)
    {
        QString text ;
        for (auto it = allMap->begin();it !=allMap->end();++it)
        {
            text+=it->first;
            text+=" | ";
            text+=it->second;
            text+="\n";
        }
        testEditor->setText(text);
    }
}
