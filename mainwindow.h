#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QDir>
#include <QFile>
#include <unordered_map>
#include <QToolBar>
#include "gamefiles.h"
#include "maineditor.h"
#include <writeplacedialog.h>
#include <modifView.h>
#include "toolbar.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString gameName;

    QDir *dirProgram;
    QDir *placeGame;
    QDir *placeMod;
public:

    static std::unordered_map<QString, QString>  allGameBase;

    ToolBar* toolBar;
    GameFiles* gameFiles;
    MainEditor* mainEditor;
    ModifView* modifView;

    WritePlaceDialog* dirFinder;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getPlaceGame();
    QString getPlaceMod();



public slots:
    void returnFiles();
};
#endif // MAINWINDOW_H
