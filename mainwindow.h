#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include <QDir>
#include <QApplication>
#include <QFile>
#include <unordered_map>
#include <QToolBar>
#include <QShortcut>
#include "gamefiles.h"
#include "maineditor.h"
#include <writeplacedialog.h>
#include <modifView.h>
#include "toolbar.h"
#include "findtextdialog.h"


enum TYPE_MOD
{
    EU_BEGIN,
    EU_IDEAS,
    EU_EVENTS,
    EU_END
};

using gameModif = std::vector<std::pair<TYPE_MOD, localMap>>;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QApplication* mainApp;
    QString gameName;
    std::unordered_map<QString, QString>::iterator nowGame;
    QDir *dirProgram;
    QDir *placeGame;
    QDir *placeMod;

    gameModif* modMap;

    void setStyleNight();
    void setStyleLight();

public:

    static std::unordered_map<QString, QString>  allGameBase;

    ToolBar* toolBar;
    GameFiles* gameFiles;
    MainEditor* mainEditor;
    ModifView* modifView;

    FindTextDialog* textFinder;
    WritePlaceDialog* dirFinder;

    MainWindow(QWidget *parent = nullptr, QApplication* in_mainApp = nullptr);
    ~MainWindow();

    QString getPlaceGame();
    QString getPlaceMod();

    void startReadParameters();



public slots:
    void returnFiles();
    void slotPress_ctrlS();
    void slotPress_ctrlShiftS();
    void slotPress_ctrlW();
    void slotPress_ctrlShiftW();

    void slotPress_ctrlC(); // there is no direct keyboard binding
    void slotPress_ctrlX(); // there is no direct keyboard binding
    void slotPress_ctrlV(); // there is no direct keyboard binding
    void slotPress_ctrlZ(); // there is no direct keyboard binding
    void slotPress_ctrlY(); // there is no direct keyboard binding
    void slotPress_ctrlF();



};
#endif // MAINWINDOW_H
