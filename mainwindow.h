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
#include <QShortcut>
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

    QShortcut* key_ctrlS;

public:

    static std::unordered_map<QString, QString>  allGameBase;

    ToolBar* toolBar;
    GameFiles* gameFiles;
    MainEditor* mainEditor;
    ModifView* modifView;

    WritePlaceDialog* dirFinder;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getPlaceGame();
    QString getPlaceMod();



public slots:
    void returnFiles();
    void slotPress_ctrlS();
    void slotPress_ctrlShiftS();
    void slotPress_ctrlW();
    void slotPress_ctrlShiftW();
};
#endif // MAINWINDOW_H
