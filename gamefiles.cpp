#include "gamefiles.h"
#include <QDebug>
#include <QVBoxLayout>

GameFiles::GameFiles(QWidget *parent) : QWidget(parent)
{
    fileModel = new QFileSystemModel(this);
    //fileModel->
    fileModel->setRootPath("");

    mainTree = new QTreeView(this);
    mainTree->setModel(fileModel);
    mainTree->hideColumn(1);
    mainTree->hideColumn(2);
    mainTree->hideColumn(3);
    //fileModel->data();

    favouritesModel = new QFileSystemModel(this);
    favouritesTree = new QTreeView(this);
    favouritesTree->setModel(favouritesModel);

    connect(mainTree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(openFiles(QModelIndex)));


    splitter = new QSplitter(this);
    layout = new QVBoxLayout(this);
    //favouritesTree->setModel(new Model);
    splitter->setOrientation(Qt::Vertical);
    splitter->setHandleWidth(1);
    splitter->addWidget(mainTree);
    splitter->addWidget(favouritesTree);
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);
    //qDebug() << mainTree[0];
     //setRootIsDecorated(false) // for two tree

}

void GameFiles::openFiles(const QModelIndex& index)
{
    favouritesTree->
    qDebug() << "openF";
}
