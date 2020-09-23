#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
#include <QMenuBar>

std::unordered_map<QString, QString> MainWindow::allGameBase
{
    {"Europa Universalis IV", "eu4"}
};

MainWindow::MainWindow(QWidget *parent, QApplication* in_mainApp)
    : QMainWindow(parent)
{
    qDebug() << this;
    mainApp = in_mainApp;
    //create main widgets
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
    mainLayout->addWidget(toolBar, 0);
    mainLayout->addWidget(centralSplitter, 1);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    QMenu* file_menuBar = menuBar()->addMenu(tr("File"));
    QMenu* options_menuBar = menuBar()->addMenu(tr("Options"));

    QAction* lightStyleAction = new QAction("light style", this);
    connect(lightStyleAction, &QAction::triggered, this, &MainWindow::setStyleLight);
    options_menuBar->addAction(lightStyleAction);

    QAction* nightStyleAction = new QAction("night style", this);
    connect(nightStyleAction, &QAction::triggered, this, &MainWindow::setStyleNight);
    options_menuBar->addAction(nightStyleAction);





    resize(1024, 720);

    dirProgram = new QDir(QCoreApplication::applicationDirPath());
    dirProgram->mkdir("ProgramFiles");
    placeGame = new QDir("");
    placeMod = new QDir("");

    QShortcut* key_ctrlS = new QShortcut(this);
    key_ctrlS->setKey(Qt::CTRL + Qt::Key_S);
    connect(key_ctrlS, SIGNAL(activated()), this, SLOT(slotPress_ctrlS()));

    QShortcut* key_ctrlShiftS = new QShortcut(this);
    key_ctrlShiftS->setKey(Qt::CTRL + Qt::SHIFT + Qt::Key_S);
    connect(key_ctrlShiftS, SIGNAL(activated()), this, SLOT(slotPress_ctrlShiftS()));

    QShortcut* key_ctrlW = new QShortcut(this);
    key_ctrlW->setKey(Qt::CTRL + Qt::Key_W);
    connect(key_ctrlW, SIGNAL(activated()), this, SLOT(slotPress_ctrlW()));

    QShortcut* key_ctrlShiftW = new QShortcut(this);
    key_ctrlShiftW->setKey(Qt::CTRL + Qt::SHIFT + Qt::Key_W);
    connect(key_ctrlShiftW, SIGNAL(activated()), this, SLOT(slotPress_ctrlShiftW()));

    QShortcut* key_ctrlF = new QShortcut(this);
    key_ctrlF->setKey(Qt::CTRL + Qt::Key_F);
    connect(key_ctrlF, SIGNAL(activated()), this, SLOT(slotPress_ctrlF()));

    textFinder = new FindTextDialog(this);

    dirFinder = new WritePlaceDialog(this);
    show();
    connect(dirFinder, SIGNAL(finished(int)), this, SLOT(returnFiles()));
    dirFinder->open();
}

void MainWindow::startReadParameters()
{
    if (nowGame->second == "eu4")
    {
        qDebug() << "start par";
        QDir(QCoreApplication::applicationDirPath()).mkdir("euFiles");
        QString parFiles(QCoreApplication::applicationDirPath() + "//euFiles");
        localMap tempMap;
        //std::make_pair<TYPE_MOD::EU, localMap>(TYPE_MOD::IDEAS, tempMap);
        //modMap->push_back(std::make_pair<TYPE_MOD::EU, localMap>(TYPE_MOD::IDEAS, tempMap));
        //YAML::reedFile(parFiles + "ideas.txt" ,(modMap->back().second));


    }
    //qDebug() << modMap->back().second.begin()->second;

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
        QFileInfo gameFile(placeGame->path() + "//" + it->second + ".exe");
        if (!(gameFile.exists() && gameFile.isFile()))
        {
            dirFinder->setLiteInfProgram(it->second + " not find in directory");
            dirFinder->open();
            return;
        }
        //if all normal
        qDebug() << "start writing dir mod and game";
        nowGame = it;
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

        startReadParameters();
        qDebug() << "dialog work";


    }
    return;
}


MainWindow::~MainWindow()
{
}

void MainWindow::setStyleNight()
{
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    //setPalette(darkPalette);
    mainApp->setPalette(darkPalette);
    //(qApp)->setPalette(darkPalette);
    //qApp->setP
    /*
    toolBar->setPalette(darkPalette);
    gameFiles->setPalette(darkPalette);
    mainEditor->setPalette(darkPalette);
    modifView->setPalette(darkPalette);
    textFinder->setPalette(darkPalette);*/


}

void MainWindow::setStyleLight()
{
    setPalette(style()->standardPalette());
}

QString MainWindow::getPlaceGame()
{
    return placeGame->absolutePath();
}

QString MainWindow::getPlaceMod()
{
    return placeMod->absolutePath();
}

void MainWindow::slotPress_ctrlS()
{
    qDebug() << "ctrl S";
    mainEditor->saveFile();
}

void MainWindow::slotPress_ctrlShiftS()
{
    qDebug() << "ctrl shift S";
    mainEditor->saveAllFile();
}

void MainWindow::slotPress_ctrlW()
{
    qDebug() << "ctrl W";
    mainEditor->closeFile();
}
void MainWindow::slotPress_ctrlShiftW()
{
    qDebug() << "ctrl shift W";
    mainEditor->closeAllFile();
}

void MainWindow::slotPress_ctrlC()
{
    mainEditor->copyText();
}
void MainWindow::slotPress_ctrlX()
{
    mainEditor->cutText();
}
void MainWindow::slotPress_ctrlV()
{
    mainEditor->pasteText();
}
void MainWindow::slotPress_ctrlZ()
{
    mainEditor->backText();
}
void MainWindow::slotPress_ctrlY()
{
    mainEditor->forwardText();
}
void MainWindow::slotPress_ctrlF()
{
    textFinder->startWork();
}
