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
    modifView = new ModifView(this);
    QSplitter *centralSplitter = new QSplitter(this);
    centralSplitter->setHandleWidth(0);
    setCentralWidget(centralSplitter);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);
    centralSplitter->addWidget(modifView);
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
        if (it == allGameBase.end())
        {
            dirFinder->setLiteInfProgram("The selected game is not supported");
            dirFinder->open();
            return;
        }
        QFileInfo gameFile(placeGame->path() + "//" + it->second);
        if (!(gameFile.exists() && gameFile.isFile()))
        {
            dirFinder->setLiteInfProgram(it->second + " not find in directory");
            dirFinder->open();
            return;
        }
        //if all normal
        QFile writePlaceGame(dirProgram->absolutePath() + "//ProgramFiles//placeGame.txt");
        writePlaceGame.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceGame(&writePlaceGame);
        writerPlaceGame << placeGame->absolutePath();
        writePlaceGame.close();
        QFile writePlaceMod(dirProgram->absolutePath() + "//ProgramFiles//placeMod.txt");
        writePlaceMod.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceMod(&writePlaceMod);
        writerPlaceMod << placeMod->absolutePath();
        writePlaceMod.close();
        gameFiles->setGamePlace(placeGame->absolutePath());
        gameFiles->setModPlace(placeMod->absolutePath());

        //qDebug() << gameFile.path();


    }
    return;
}


MainWindow::~MainWindow()
{
}

QString MainWindow::getPlaceGame()
{
    return placeGame->absolutePath();
}

QString MainWindow::getPlaceMod()
{
    return placeMod->absolutePath();
}

