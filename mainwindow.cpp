#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
#include <QMenuBar>

std::unordered_map<QString, QString> MainWindow::allGameBase
{
    {"Europa Universalis IV", "eu4.exe"}
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout(mainWidget);

    gameFiles = new GameFiles(mainWidget);
    mainEditor = new MainEditor(mainWidget);
    modifView = new ModifView(mainWidget);
    QSplitter *centralSplitter = new QSplitter(mainWidget);
    centralSplitter->setHandleWidth(0);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);
    centralSplitter->addWidget(modifView);
    centralSplitter->setStretchFactor(0, 20);
    centralSplitter->setStretchFactor(1, 80);
    centralSplitter->setStretchFactor(2, 30);

    toolBar = new ToolBar(mainWidget);
    mainLayout->addWidget(toolBar);
    mainLayout->addWidget(centralSplitter);
    mainLayout->setContentsMargins(0,0,0,0);

    resize(1024, 720);

    dirProgram = new QDir(QCoreApplication::applicationDirPath());
    dirProgram->mkdir("ProgramFiles");

    placeGame = new QDir("");
    placeMod = new QDir("");

    menuBar()->addMenu(tr("&File"));

    dirFinder = new WritePlaceDialog(this);
    show();
    connect(dirFinder, SIGNAL(finished(int)), this, SLOT(returnFiles()));
    dirFinder->open();
}

void MainWindow::returnFiles()
{
    qDebug() << "returns places mod and game from the dialog";
    placeGame->cd(dirFinder->getNowPlaceGame());
    placeMod->cd(dirFinder->getNowPlaceMod());
    if (!(placeGame->cd(dirFinder->getNowPlaceGame()) && (placeGame->path() != ".") &&
            placeMod->cd(dirFinder->getNowPlaceMod()) && (placeMod->path() != ".")))
    {
        qDebug() << "problems with dir";
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
        qDebug() << "start writing dir mod and game";
        QFile writePlaceGame(dirProgram->absolutePath() + "//ProgramFiles//placeGame.txt");
        writePlaceGame.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceGame(&writePlaceGame);
        writerPlaceGame << placeGame->absolutePath();
        writePlaceGame.close();
        qDebug() << "1";
        QFile writePlaceMod(dirProgram->absolutePath() + "//ProgramFiles//placeMod.txt");
        writePlaceMod.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceMod(&writePlaceMod);
        writerPlaceMod << placeMod->absolutePath();
        writePlaceMod.close();
        qDebug() << "2";
        gameFiles->setGamePlace(placeGame->absolutePath());
        gameFiles->setModPlace(placeMod->absolutePath());
        qDebug() << "3";

        modifView->localOpener();
        qDebug() << "dialog work";


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

