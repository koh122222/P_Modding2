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
#include <QFile>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QFile *ProgramFilesF;

    QDir *dirProgram;
    QDir *placeGame;
    QDir *placeMod;
public:
    GameFiles* gameFiles;
    MainEditor* mainEditor;

    WritePlaceDialog* dirFinder;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QFile* getProgramFilesF();

public slots:
    void returnFiles();
};
#endif // MAINWINDOW_H
