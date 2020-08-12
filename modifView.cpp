#include "modifView.h"
#include "primparseryaml.h"
#include "mainwindow.h"
#include <QDebug>
ModifView::ModifView(QWidget *parent) : QWidget(parent)
{
    testEditor = new QTextEdit(this);
    layout = new QGridLayout(this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(testEditor);
}

void ModifView::localOpener()
{
    qDebug()<<"1";
    QString filePlace = static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceGame();
    qDebug() << "2";
    filePlace+="/localisation";

    localMap * tagLocal = new localMap;
    //qDebug()<<filePlace;
    YAML::reedFile(filePlace+"/countries_l_english.yml",*tagLocal);
    //QString text;

    for (auto it = tagLocal->begin();it !=tagLocal->end();++it)
    {
        it->first;
        it->second;
    }
    //qDebug()<<"end";
    //testEditor->setText(text);
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
