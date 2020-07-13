#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1024, 720);
    gameFiles = new GameFiles(this);
    mainEditor = new MainEditor(this);
    QSplitter *centralSplitter = new QSplitter(this);
    centralSplitter->setHandleWidth(0);
    setCentralWidget(centralSplitter);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);
    centralSplitter->setStretchFactor(0, 20);
    centralSplitter->setStretchFactor(1, 80);

    dirFinder = new WritePlaceDialog(this);
    show();
    returnFiles();
    qDebug() << "tst";

}

void MainWindow::returnFiles()
{
    placeGame->cd(dirFinder->getNowPlaceGame());
    placeMod->cd(dirFinder->getNowPlaceMod());
    if (!(placeGame->exists() || placeGame->exists()))
    {
        dirFinder->open();
    }
    //placeGame = dirFinder->getNowPlaceGame();
    //placeMod = dirFinder->getNowPlaceMod();
    //QDir::exists(placeGame);
    return;
}

MainWindow::~MainWindow()
{
}


