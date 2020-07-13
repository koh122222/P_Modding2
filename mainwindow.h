#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QDir>
#include "gamefiles.h"
#include "maineditor.h"
#include <writeplacedialog.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QDir *placeGame;
    QDir *placeMod;
public:
    GameFiles* gameFiles;
    MainEditor* mainEditor;

    WritePlaceDialog* dirFinder;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void returnFiles();
};
#endif // MAINWINDOW_H
