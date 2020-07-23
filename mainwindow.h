#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QDir>
#include <QFile>
#include <unordered_map>
#include "gamefiles.h"
#include "maineditor.h"
#include <writeplacedialog.h>
#include <modifView.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString gameName;

    QDir *dirProgram;
    QDir *placeGame;
    QDir *placeMod;
public:

    static std::unordered_map<QString, QString>  allGameBase;

    GameFiles* gameFiles;
    MainEditor* mainEditor;
    ModifView* moddifView;

    WritePlaceDialog* dirFinder;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString get_placeGame();



public slots:
    void returnFiles();
};
#endif // MAINWINDOW_H
