#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameFiles = new GameFiles(this);
    mainEditor = new MainEditor(this);
    QSplitter *centralSplitter = new QSplitter(this);
    centralSplitter->setHandleWidth(1);
    setCentralWidget(centralSplitter);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);
}

MainWindow::~MainWindow()
{
}

