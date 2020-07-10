#include "gamefiles.h"
#include <QDebug>
#include <QVBoxLayout>

GameFiles::GameFiles(QWidget *parent) : QWidget(parent)
{
    fileModel = new QFileSystemModel(this);
    fileModel->setRootPath("");

    mainTree = new QTreeView(this);
    mainTree->setModel(fileModel);

    favouritesTree = new QTreeView(this);
    //QVBoxLayout *layout = new Q
    splitter = new QSplitter(this);
    //favouritesTree->setModel(new Model);
    splitter->setOrientation(Qt::Vertical);
    splitter->setHandleWidth(1);

    splitter->addWidget(mainTree);
    splitter->addWidget(favouritesTree);
    //layout->addWidget(firstTextEdit);
    //layout->setContentsMargins(0,0,0,0);
    //setLayout(layout);

     //setRootIsDecorated(false) // for two tree

}
