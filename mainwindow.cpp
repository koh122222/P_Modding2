#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
std::unordered_map<QString, QString> MainWindow::allGameBase
{
    {"Europa Universalis IV", "eu4.exe"}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(1024, 720);
    gameFiles = new GameFiles(this);
    mainEditor = new MainEditor(this);
    moddifView = new ModdifView(this);
    QSplitter *centralSplitter = new QSplitter(this);
    centralSplitter->setHandleWidth(0);
    setCentralWidget(centralSplitter);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);
    centralSplitter->addWidget(moddifView);
    centralSplitter->setStretchFactor(0, 20);
    centralSplitter->setStretchFactor(1, 80);
    centralSplitter->setStretchFactor(2, 30);

    dirProgram = new QDir(QCoreApplication::applicationDirPath());
    dirProgram->mkdir("ProgramFiles");

    placeGame = new QDir("");
    placeMod = new QDir("");

    dirFinder = new WritePlaceDialog(this);
    show();
    connect(dirFinder, SIGNAL(finished(int)), this, SLOT(returnFiles()));
    dirFinder->open();
}

void MainWindow::returnFiles()
{
    placeGame->cd(dirFinder->getNowPlaceGame());
    qDebug() << placeGame->absolutePath();
    placeMod->cd(dirFinder->getNowPlaceMod());
    if (!(placeGame->cd(dirFinder->getNowPlaceGame()) && (placeGame->path() != ".") &&
            placeMod->cd(dirFinder->getNowPlaceMod()) && (placeMod->path() != ".")))
    {
        dirFinder->setLiteInfProgram("Dir problem");
        dirFinder->open();
        return;
    }
    else
    {
        std::unordered_map<QString, QString>::iterator it = allGameBase.find(dirFinder->getNowGame());
        qDebug() << "1";
        if (it == allGameBase.end())
        {
            qDebug() << ("2");
            dirFinder->setLiteInfProgram("The selected game is not supported");
            dirFinder->open();
            return;
        }
        qDebug() << placeGame->path();
        qDebug() << placeGame->absolutePath();
        QFileInfo gameFile(placeGame->path() + "//" + it->second);
        qDebug() << gameFile.absoluteFilePath();
        if (!(gameFile.exists() && gameFile.isFile()))
        {
            qDebug() << "3";
            dirFinder->setLiteInfProgram(it->second + " not find in directory");
            dirFinder->open();
            return;
        }
        //if all normal
        QFile writePlaceGame("ProgramFiles//placeGame.txt");
        writePlaceGame.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceGame(&writePlaceGame);
        writerPlaceGame << placeGame->absolutePath();
        writePlaceGame.close();
        QFile writePlaceMod("ProgramFiles//placeMod.txt");
        writePlaceMod.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceMod(&writePlaceMod);
        writerPlaceMod << placeMod->absolutePath();
        writePlaceMod.close();

        //qDebug() << gameFile.path();


    }
    return;
}

MainWindow::~MainWindow()
{
}


