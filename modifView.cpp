#include "modifView.h"
#include "mainwindow.h"
#include <QDebug>
#include <QStringList>
#include <QDir>
#include <QFile>

ModifView::ModifView(QWidget *parent) : QWidget(parent)
{
    testEditor = new QTextEdit(this);
    layout = new QGridLayout(this);
    allFilter = new QCheckBox("All",this);
    textFilter = new QCheckBox("Text",this);
    tagFilter = new QCheckBox("Tag",this);
    modifierFilter = new QCheckBox("Modifier",this);
    eventFilter = new QCheckBox("Event",this);
    opener = new QPushButton("ModOp",this);

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(allFilter,0,0);
    layout->addWidget(textFilter,0,1);
    layout->addWidget(tagFilter,0,2);
    layout->addWidget(eventFilter,0,3);
    layout->addWidget(modifierFilter,0,4);
    layout->addWidget(opener,0,6);
    layout->addWidget(testEditor,1,0,1,7);

    connect(allFilter, SIGNAL(stateChanged(int)), this, SLOT(allPrint(int)));
    connect(textFilter, SIGNAL(stateChanged(int)), this, SLOT(textPrint(int)));
    connect(tagFilter, SIGNAL(stateChanged(int)), this, SLOT(tagPrint(int)));
    connect(eventFilter, SIGNAL(stateChanged(int)), this, SLOT(eventPrint(int)));
    connect(modifierFilter, SIGNAL(stateChanged(int)), this, SLOT(modifierPrint(int)));
    connect(opener, SIGNAL(clicked()), this, SLOT(modifierOpener()));
}

void ModifView::modifierOpener()
{
    localOpener();
    ideasOpen ();


    modifierMap = new localMap;
    for (auto it = allMap->begin();it !=allMap->end();++it)
    {
        QString TechName = it->first;
        QString LocalName = it->second;
        for (int i = 0; i<modifiers.size();++i)
            if ((modifiers[i]+":0"== TechName) || ("custom_idea_"+modifiers[i]+":0"== TechName))
            {
               // qDebug()<<modifiers[i]/*.mid(modifiers[i].lastIndexOf(TechName),TechName.size())*/;
                //qDebug()<<i;
                modifierMap->insert(localMap::value_type(TechName,LocalName));
            }
    }
}

void ModifView::ideasOpen ()
{

    QString ideas;
    QString filePlace = static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceGame();
    filePlace+="/common/ideas";
    QDir local(filePlace);
    std::vector<QString> names = {"00_basic_ideas.txt",
                                 "00_country_ideas.txt",
                                 "zz_group_ideas.txt",
                                "zzz_default_idea.txt",
                                 "zzzz_compatibility.txt"};
    //QStringList names = local.entryList();
    //qDebug()<<"Кох - пидор 1";
    for (int i = 0; i< names.size();++i)
    {
        //qDebug()<<"Кох - пидор 2";
        QFile ideaFile(filePlace+"/"+names[i]);
        ideaFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream idea_file(&ideaFile);
        ideas += idea_file.readAll();
        //qDebug()<<idea_file.readAll();
        ideaFile.close();


        bool modifier = false;
        QString pre_modFile;
        for (int i = 0;i < ideas.size();++i)
        {
            //qDebug()<<"Кох - пидор 3";
             if (modifier)
                pre_modFile+=ideas[i];
             if (i>13)
                if (((ideas[i]=="{")
                    &&!(ideas.mid(i-8,5)=="ideas")
                    &&!(ideas.mid(i-10,7)=="trigger")
                    &&!(ideas.mid(i-5,2)=="OR")
                    &&!(ideas.mid(i-6,3)=="NOT")
                    &&!(ideas.mid(i-13,10)=="ai_will_do")
                    &&!(ideas.mid(i-21,18)=="any_owned_province")
                    &&!(ideas.mid(i-16,13)=="capital_scope")
                    &&!(ideas.mid(i-11,8)=="modifier")))
                    modifier = true;
             if (i<ideas.size()-1)
                if(ideas[i+1]=="}")
                    modifier = false;
        }

        QString uncleanFile;
        bool contin = true;
        bool trash = false;
        for (int i = 0;i < pre_modFile.size();++i)
        {
            if (i < pre_modFile.size()-4)
            {
                if ((pre_modFile[i]=="#")
                    ||(pre_modFile[i]=="=")
                    ||(pre_modFile.mid(i,3)=="tag")
                    ||(pre_modFile.mid(i,3)=="TAG")
                    ||(pre_modFile.mid(i,3)=="AND")
                    ||(pre_modFile.mid(i,3)=="NOT")
                    ||(pre_modFile.mid(i,2)=="OR")
                    ||(pre_modFile.mid(i,7)=="dynasty")
                    ||(pre_modFile.mid(i,5)=="allow")
                    ||(pre_modFile.mid(i,5)=="start")
                    ||(pre_modFile.mid(i,9)=="religion ")
                    ||(pre_modFile.mid(i,6)=="region")
                    ||(pre_modFile.mid(i,8)=="category")
                    ||(pre_modFile.mid(i,13)=="culture_group")
                    ||(pre_modFile.mid(i,15)=="primary_culture"))
                    trash = true;
            }
            if (pre_modFile[i]==" ")
                contin = false;
            if (trash)
                contin = false;
            if (pre_modFile[i]=="\n")
                trash = false;
            if ((contin)||(pre_modFile[i]=="\n"))
                uncleanFile += pre_modFile[i];
            contin = true;

        }
        QString idModifiers;
        for (int i =0; i < uncleanFile.size(); ++i)
        {
            if (i>0)
                if ((uncleanFile[i]=="\n")&&(uncleanFile[i - 1]!="\n")&&(uncleanFile[i - 1]!="\t"))
                    idModifiers += "\n";
            if ((uncleanFile[i]!="\n")&&(uncleanFile[i]!="\t"))
                idModifiers += uncleanFile[i];
        }
        int lenght = 0;
        for (int i = 0 ; i<idModifiers.size(); ++i)
        {
            if (idModifiers[i]=="\n")
            {
                QString newMod = idModifiers.mid(i - lenght,lenght);
                lenght = -1;
                bool unique = true;
                for (int i = 0; i <  modifiers.size(); ++i)
                {
                    if ( modifiers[i]==newMod)
                        unique = false;
                }
                if (unique)
                {
                     modifiers.push_back(newMod);
                     //qDebug()<<newMod;
                }
            }
            ++lenght;
        }
    }
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

void ModifView::modifierPrint(int a)
{
    testEditor->setText("");
    if (a)
    {
        QString text ;
        for (auto it = modifierMap->begin();it !=modifierMap->end();++it)
        {
            text+=it->first;
            text+=" | ";
            text+=it->second;
            text+="\n";
            //qDebug()<<"Кох - пидор";
        }
        testEditor->setText(text);
        currentText = text;
    }
}

void ModifView::eventPrint(int a)
{
    testEditor->setText("");
    if (a)
    {
        QString text ;
        for (auto it = eventMap->begin();it !=eventMap->end();++it)
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


