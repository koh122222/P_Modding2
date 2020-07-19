#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QDir>
#include <QFile>
#include "gamefiles.h"
#include "maineditor.h"
#include <writeplacedialog.h>
#include <moddifView.h>

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
    ModdifView* moddifView;

    WritePlaceDialog* dirFinder;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QFile* getProgramFilesF();

public slots:
    void returnFiles();
};
#endif // MAINWINDOW_H
