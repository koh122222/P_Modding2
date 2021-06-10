#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
#include <QDir>
#include <QCoreApplication>
#include <QFileInfo>
#include <QMenuBar>
#include <QHash>
#include <QSet>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //setStyleNight();
    AllPar::mObject = this;
    customInterface = new CustomInterfaceDialog(this);
    qDebug() << AllPar::mObject;
    //create main widgets
    QWidget* mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout(mainWidget);

    gameFiles = new GameFiles(mainWidget);
    mainEditor = new MainEditor(mainWidget);
    parView = new ParView(mainWidget);
    QSplitter *centralSplitter = new QSplitter(mainWidget);
    centralSplitter->setHandleWidth(0);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);
    centralSplitter->addWidget(parView);
    centralSplitter->setStretchFactor(0, 20);
    centralSplitter->setStretchFactor(1, 80);
    centralSplitter->setStretchFactor(2, 30);
    centralSplitter->setStretchFactor(3, 20);

    toolBar = new ToolBar(mainWidget);
    mainLayout->addWidget(toolBar, 0);
    mainLayout->addWidget(centralSplitter, 1);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);

    QMenu* fileMenuBar = menuBar()->addMenu(tr("File"));
    QMenu* optionsMenuBar = menuBar()->addMenu(tr("Options"));

    QAction* themeAction = new QAction("Theme Options", this);
    connect(themeAction, &QAction::triggered, this, &MainWindow::themeDialogOpen);
    optionsMenuBar->addAction(themeAction);

    resize(1024, 720);

    AllPar::modVector.resize(TYPE_MOD::M_END_TYPE);

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
        YAML::reedFile(parFiles + "//eu_ideas.txt", AllPar::modVector[TYPE_MOD::M_EU_IDEAS]);
        YAML::reedFile(parFiles + "//eu_events.txt", AllPar::modVector[TYPE_MOD::M_EU_EVENTS]);
        for (auto c : AllPar::modVector[TYPE_MOD::M_EU_IDEAS])
            qDebug() << c;
        for (auto c : AllPar::modVector[TYPE_MOD::M_EU_EVENTS])
            qDebug() << c;
        for (auto c : AllPar::modVector[TYPE_MOD::M_EU_EVENTS])
            qDebug() << c;
        //qDebug() << modMap[TYPE_MOD::EU_IDEAS].key("OR");
        //modMap->push_back(tempMap);
        //YAML::reedFile(parFiles + "ideas.txt" ,(modMap->back().second));


    }
    //qDebug() << modMap->back().second.begin()->second;

}

void MainWindow::updateParameters()
{

}

void MainWindow::themeDialogOpen()
{
    customInterface->showStart();
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
        std::unordered_map<QString, QString>::iterator it = AllPar::allGameBase.find(dirFinder->getNowGame());
        if (it == AllPar::allGameBase.end())
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
        writePlaceGame.open(QFile::Text | QFile::ReadOnly);
        QTextStream oldGameStream(&writePlaceGame);
        QSet<QString> oldGamePlace;
        while (!oldGameStream.atEnd())
            oldGamePlace.insert(oldGameStream.readLine());
        writePlaceGame.close();
        {
        auto c = oldGamePlace.find(placeGame->absolutePath());
        if (c != oldGamePlace.end())
            oldGamePlace.erase(c);
        }
        writePlaceGame.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceGame(&writePlaceGame);
        writerPlaceGame << placeGame->absolutePath() << "\n";
        {
            qint32 i = 0;
            for (auto c = oldGamePlace.end(); c != oldGamePlace.begin() && i < 5; ++i)
            {
                --c;
                writerPlaceGame << *c << "\n";
            }
        }



        QFile writePlaceMod(dirProgram->absolutePath() + "//ProgramFiles//placeMod.txt");
        writePlaceMod.open(QFile::Text | QFile::ReadOnly);
        QTextStream oldModStream(&writePlaceMod);
        QSet<QString> oldModPlace;
        while (!oldModStream.atEnd())
            oldModPlace.insert(oldModStream.readLine());
        writePlaceMod.close();
        qDebug() << "end QSet";
        {
        auto c = oldModPlace.find(placeMod->absolutePath());
        if (c != oldModPlace.end())
            oldModPlace.erase(c);
        }
        qDebug() << "end delete old";
        writePlaceMod.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceMod(&writePlaceMod);
        writerPlaceMod << placeMod->absolutePath() << "\n";
        {
            qint32 i = 0;
            for (auto c = oldModPlace.end(); c != oldModPlace.begin() && i < 5; ++i)
            {
                --c;
                writerPlaceMod << *c << "\n";
            }
        }

        /*
        QFile writePlaceMod(dirProgram->absolutePath() + "//ProgramFiles//placeMod.txt");
        writePlaceMod.open(QFile::Text | QFile::ReadOnly);
        QSet<QString> oldGameMod;
        w



        writePlaceMod.open(QFile::Text | QFile::WriteOnly);
        QTextStream writerPlaceMod(&writePlaceMod);
        writerPlaceMod << placeMod->absolutePath();
        writePlaceMod.close();*/
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
    /*
    std::unordered_map<QString, QString> iColors = AllPar::interface_colors[AllPar::VT_DARK];
    qDebug() << iColors["mainColor"]; //color: #dedede
    qApp->setStyleSheet(
            "QWidget"
            "{"
            "   background-color: " + iColors["mainBGColor"] + ";"
            "   color: " + iColors["mainTextColor"] + ";"
            "}"
            "QLineEdit"
            "{"
            "   background-color: " + iColors["mainBGColor"] + ";"
            "   border-radius: 1px;"
            "   border-style: outset;"
            "   border-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ""
            "}"
            "QPlainTextEdit"
            "{"
            "   background-color: " + iColors["mainBGColor"] + ";"
            "}"
            "QToolBar"
            "{"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "   border-bottom-width: 1px;"
            "   border-top-width: 1px;"
            "   border-style: solid;"
            "   border-color: " + iColors["lightBorderColor2"] + ";"
            "}"
            "QToolButton"
            "{"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "}"
            "QToolButton:hover"
            "{"
            "   background-color: " + iColors["selectBGColor"] + ";"
            "}"
            "QTabWidget:pane"
            "{"
            "   margin: 0px 0px 0px 0px"
            "}"
            "QTabBar::tab"
            "{"
            "   margin: 0px 0px 0px 0px;"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "   height: 1.2em;"
            "   border-left-width: 1px;"
            "   border-right-width: 1px;"
            "   padding-bottom: -1px;"
            "}"
            "QHeaderView::section"
            "{"
            "   margin: 0px 0px 0px 0px;"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "   border-style: solid;"
            "   border-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "   border-right-width: 0px;"
            "   border-left-width: 0px;"
            "   height: 1.2em;"
            "}"


            "QScrollBar:vertical "
            "{"
            "   border-style: solid;"
            "   border-width: 1px;"
            "   border-right-width: 0px;"
            "   border-color:" + iColors["lightBorderColor"] + ";"
            "   background-color:" + iColors["secondBGColor"] + ";"
            "   width: 14px;"
            "   margin: 13px 0px 13px 0px;"
            "}"
            "QScrollBar::handle:vertical {"
            "   background-color: " + iColors["scrollHandle"] + ";"
            "   border-style: solid;"
            "   border-width: 1px;"
            "   border-color: " + iColors["lightBorderColor3"] + ";"
            "   min-height: 20px;"
            "}"
            "QScrollBar::add-line:vertical {"
            "   border-left-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "   border-style: solid;"

            //"   margin: 1px 1px 1px 1px;"
            "   height: 13px;"
            "   subcontrol-position: bottom;"
            "   subcontrol-origin: margin;"
            "   background-image: url(:/resources/interfaceImage/arrow_bottom.png);"
            "}"

            "QScrollBar::sub-line:vertical {"
            "   border-left-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "   border-style: solid;"
            "   height: 13px;"
            "   subcontrol-position: top;"
            "   subcontrol-origin: margin;"
            "   background-image: url(:/resources/interfaceImage/arrow_top.png);"
            "}"
            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
            "    background: none;"
            "}"
            "QTreeView"
            "{"
            "   border-style: solid;"
            "   border-width: 0px;"
            "   border-right-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "}"
            "QMenuBar"
            "{"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "}"
            "QMenuBar:item:selected"
            "{"
            "   background-color: " + iColors["selectBGColor"] + ";"
            "}"
            "QMenu"
            "{"
            "   margin: 0px 0px 0px 0px;"
            "   border-style: solid;"
            "   border-top-width: 1px;"
            "   border-color: " + iColors["lightBorderColor2"] + ";"
            "}"
            "QMenu::item"
            "{"
            "   height: 1.6em"

            "}"
            "QMenu::item:selected"
            "{"
            "   background-color: " + iColors["selectBGColor2"] + ";"
            "}"
            "QComboBox"
            "{"
            //"   border: 2px solid "
            "   height: 1.3em;"
            "}"
            "QComboBox QAbstractItemView::item"
            "{"
            "   background-color" + iColors["mainBGColor"] + ";"
            "}"

        );
*/
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

void MainWindow::greatBUTTON()
{
    AllPar::modVector[M_EU_IDEAS].insert(ModModel::value_type("testIdea1", "testIdea111111"));
    qDebug() << AllPar::modVector[M_EU_IDEAS].mainItems();
}
