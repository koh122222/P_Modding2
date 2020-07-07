#include "mainwindow.h"
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    gameFiles = new GameFiles(this);
    mainEditor = new MainEditor(this);
    QSplitter *centralSplitter = new QSplitter(this);
    setCentralWidget(centralSplitter);
    centralSplitter->addWidget(gameFiles);
    centralSplitter->addWidget(mainEditor);


}

MainWindow::~MainWindow()
{
}

