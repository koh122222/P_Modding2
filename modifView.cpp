#include "modifView.h"
#include "mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QDir>
ModifView::ModifView(QWidget *parent) : QWidget(parent)
{
    testEditor = new QTextEdit(this);
    layout = new QGridLayout(this);
    allFilter = new QCheckBox("All",this);
    textFilter = new QCheckBox("Text",this);
    tagFilter = new QCheckBox("Tag",this);
    testFilter = new QCheckBox("Test",this);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(allFilter,0,0);
    layout->addWidget(textFilter,0,1);
    layout->addWidget(tagFilter,0,2);
    layout->addWidget(testFilter,0,3);
    layout->addWidget(testEditor,1,0,1,7);

    connect(allFilter, SIGNAL(stateChanged(int)), this, SLOT(allPrint(int)));
    connect(textFilter, SIGNAL(stateChanged(int)), this, SLOT(textPrint(int)));
    connect(tagFilter, SIGNAL(stateChanged(int)), this, SLOT(tagPrint(int)));
    connect(testFilter, SIGNAL(stateChanged(int)), this, SLOT(testPrint(int)));
}

void ModifView::localOpener()
{
    QString filePlace = static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceGame();
    filePlace+="/localisation";
    QDir local(filePlace);
    QStringList names = local.entryList();

    allMap = new localMap;
    textMap = new localMap;
    tagMap = new localMap;
    eventMap = new localMap;
    for (int i = 0; i< names.size();++i)
    {
        if (names[i].right(11)=="english.yml")
        {
            YAML::reedFile(filePlace+"/"+names[i],*allMap);
        }
    }

    for (auto it = allMap->begin();it !=allMap->end();++it)
    {
        QString TechName = it->first;
        QString LocalName = it->second;
        if (messagePoint(LocalName))
        {
            textMap->insert(localMap::value_type(TechName,LocalName));
        }

        if (tagPoint(TechName)||adj_tagPoint(TechName))
        {
            tagMap->insert(localMap::value_type(TechName,LocalName));
        }
        if (eventPoint(TechName))
        {
            eventMap->insert(localMap::value_type(TechName,LocalName));
        }
    }
    //qDebug()<<tagMap->size();


    //YAML::reedFile(filePlace+"/countries_l_english.yml",*allMap);
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
    if (programText.size()==5)
        return true;
    return false;
}

bool ModifView::adj_tagPoint (QString programText)
{
    if (programText.size()==9)
        if (programText.mid(3,4) == "_ADJ")
            return true;
    return false;
}

bool ModifView::eventPoint (QString programText)
{
    if (programText.size()>=5)
    {
        QString right = programText.right (5);
        if (right.left(2) == "1.")
            return true;
        if (right.left(2) == "2.")
            return true;
        if (right.left(2) == "3.")
            return true;
        if (right.left(2) == "4.")
            return true;
        if (right.left(2) == "5.")
            return true;
        if (right.left(2) == "6.")
            return true;
        if (right.left(2) == "7.")
            return true;
        if (right.left(2) == "8.")
            return true;
        if (right.left(2) == "9.")
            return true;
        if (right.left(2) == "0.")
            return true;
    }
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
        currentText = text;
    }
}

void ModifView::textPrint(int a)
{
    testEditor->setText("");
    if (a)
    {
        QString text;
        for (auto it = textMap->begin();it !=textMap->end();++it)
        {
            text+=it->first;
            text+=" | ";
            text+=it->second;
            text+="\n";
        }
        testEditor->setText(text);
        currentText = text;
    }
}

void ModifView::testPrint(int a)
{
    testEditor->setText("");
    if (a)
    {
        QString text ;
        for (auto it = eventMap->begin();it !=eventMap->end();++it)
        {
            text+=it->first;
            text+=" | ";
            //text+=it->second;
            text+="\n";
        }
        testEditor->setText(text);
        currentText = text;
    }
}

void ModifView::tagPrint(int a)
{
    testEditor->setText("");
    if (a)
    {
        QString text;
        for (auto it = tagMap->begin();it !=tagMap->end();++it)
        {
            text+=it->first;
            text+=" | ";
            text+=it->second;
            text+="\n";
        }
        testEditor->setText(text);
        currentText = text;
    }
}


