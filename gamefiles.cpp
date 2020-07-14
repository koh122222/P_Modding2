#include "gamefiles.h"
#include "maineditor.h"
#include <mainwindow.h>
#include <QDebug>
#include <QVBoxLayout>



GameFiles::GameFiles(QWidget *parent)
    : QWidget(parent)
{
    fileModel = new onlyFileSystemModel(this);
    fileModel->setRootPath("");
    fileModel->setFirstName("Game Name");

    mainTree = new QTreeView(this);
    mainTree->setModel(fileModel);
    mainTree->hideColumn(1);
    mainTree->hideColumn(2);
    mainTree->hideColumn(3);

    favouritesModel = new onlyFileSystemModel(this);
    //favouritesModel->setRootPath("");
    favouritesModel->setFirstName("File Mod");
    favouritesTree = new QTreeView(this);
    favouritesTree->setModel(favouritesModel);
    favouritesTree->hideColumn(1);
    favouritesTree->hideColumn(2);
    favouritesTree->hideColumn(3);
    connect(mainTree, SIGNAL(doubleClicked(QModelIndex)),
            this , SLOT(openFilesG(QModelIndex)));

    splitter = new QSplitter(this);
    layout = new QVBoxLayout(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->setHandleWidth(1);
    splitter->addWidget(mainTree);
    splitter->addWidget(favouritesTree);
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);

}
//NOW ONLY FOR TXT
void GameFiles::openFilesG(const QModelIndex& index)
{
    QString openFile = fileModel->filePath(index);
    if (fileModel->isDir(index))//////
        return;
    quint32 findExtension;
    if ((findExtension = openFile.lastIndexOf('.')) == -1)
        return;
    else if (openFile.right(openFile.size() - findExtension) != ".txt")
    {
        qDebug() << openFile.right(openFile.size() - findExtension);
        return;
    }
    static_cast<MainWindow*>(parent()->parent())->mainEditor->openFiles(openFile);
}
