#include "gamefiles.h"
#include "maineditor.h"
#include <mainwindow.h>
#include <QDebug>
#include <QVBoxLayout>



GameFiles::GameFiles(QWidget *parent)
    : QWidget(parent)
{
    fileModel = new onlyFileSystemModel(this);
    fileModel->setFirstName("File Game");
    mainTree = new QTreeView(this);
    mainTree->setModel(fileModel);
    mainTree->hideColumn(1);
    mainTree->hideColumn(2);
    mainTree->hideColumn(3);
    connect(mainTree, SIGNAL(doubleClicked(QModelIndex)),
            this , SLOT(openFileFromTreeGame(QModelIndex)));

    favouritesModel = new onlyFileSystemModel(this);
    favouritesModel->setFirstName("File Mod");
    favouritesTree = new QTreeView(this);
    favouritesTree->setModel(favouritesModel);
    favouritesTree->hideColumn(1);
    favouritesTree->hideColumn(2);
    favouritesTree->hideColumn(3);
    connect(favouritesTree, SIGNAL(doubleClicked(QModelIndex)),
            this , SLOT(openFileFromTreeMod(QModelIndex)));


    splitter = new QSplitter(this);
    layout = new QVBoxLayout(this);
    splitter->setOrientation(Qt::Vertical);
    splitter->setHandleWidth(0);
    splitter->addWidget(mainTree);
    splitter->addWidget(favouritesTree);
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    setLayout(layout);

}

void GameFiles::setGamePlace(QString placeGame)
{
    QModelIndex index = fileModel->index(placeGame);
    mainTree->setRootIndex(index);
    fileModel->setRootPath(placeGame);
}

void GameFiles::setModPlace(QString placeMod)
{
    QModelIndex index = favouritesModel->index(placeMod);
    favouritesTree->setRootIndex(index);
    favouritesModel->setRootPath(placeMod);
}

void GameFiles::openFileFromTreeGame(const QModelIndex& index)
{
    openFileFromTree(index, MainEditor::GAME_FILE);
}
void GameFiles::openFileFromTreeMod(const QModelIndex& index)
{
    openFileFromTree(index, MainEditor::MOD_FILE);
}
//NOW ONLY FOR TXT
void GameFiles::openFileFromTree(const QModelIndex& index, MainEditor::FileSystem fileSystem)
{
    QString clickedFile = fileModel->filePath(index);
    if (fileModel->isDir(index))//////
        return;
    quint32 findExtension;
    if ((findExtension = clickedFile.lastIndexOf('.')) == -1)
        return;
    QStringRef fileExtension = clickedFile.rightRef(clickedFile.size() - findExtension);
    if (fileExtension == ".txt" || fileExtension == ".yml")
    {

        qDebug() << clickedFile.right(clickedFile.size() - findExtension);
        static_cast<MainWindow*>(parent()->parent()->parent())->mainEditor->openTextFile(clickedFile, fileSystem);
    }

}
