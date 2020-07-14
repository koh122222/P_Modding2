#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>

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

    dirProgram = new QDir(QCoreApplication::applicationDirPath());
    dirProgram->mkdir("ProgramFiles");
    ProgramFilesF = new QFile(dirProgram->currentPath() + "//ProgramFiles//test.txt", this);
    ProgramFilesF->open(QFile::ReadOnly | QFile::WriteOnly | QFile::Text);
    //QTextStream temp(getProgramFilesF());


    placeGame = new QDir("");
    placeMod = new QDir("");

    dirFinder = new WritePlaceDialog(this);
    show();
    connect(dirFinder, SIGNAL(finished(int)), this, SLOT(returnFiles()));
    dirFinder->open();
}

 QFile* MainWindow::getProgramFilesF()
{
     return ProgramFilesF;
}

void MainWindow::returnFiles()
{
    placeGame->cd(dirFinder->getNowPlaceGame());
    placeMod->cd(dirFinder->getNowPlaceMod());
    qDebug() << dirProgram->currentPath();
    if (!(placeGame->cd(dirFinder->getNowPlaceGame()) && (placeGame->path() != ".") &&
            placeMod->cd(dirFinder->getNowPlaceMod()) && (placeMod->path() != ".")))
    {
        dirFinder->setLiteInfProgram("Dir problem");
        dirFinder->open();
    }
    return;
}

MainWindow::~MainWindow()
{
}


