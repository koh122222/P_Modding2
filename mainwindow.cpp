#include "mainwindow.h"
#include <QSplitter>
#include <QDebug>
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

}

MainWindow::~MainWindow()
{
}

