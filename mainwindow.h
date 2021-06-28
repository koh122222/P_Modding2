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
//#include <modifViewOld.h>
#include "parareader.h"
#include "toolbar.h"
#include "findtextdialog.h"
#include "allpar.h"
#include "custominterfacedialog.h"
#include "primparseryaml.h"
#include "ParView.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString gameName;
    std::unordered_map<QString, QString>::iterator nowGame;
    QDir *dirProgram;
    QDir *placeGame;
    QDir *placeMod;


    void setStyleNight();
    void setStyleLight();

public:
    QSplitter *centralSplitter;
    static std::unordered_map<QString, QString>  allGameBase;

    //static std::array<QColor, TYPE_MOD::END_TYPE> highlighter_light;

    ToolBar* toolBar;
    GameFiles* gameFiles;
    MainEditor* mainEditor;
    ParView* parView;

    FindTextDialog* textFinder;
    WritePlaceDialog* dirFinder;
    CustomInterfaceDialog* customInterface;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString getPlaceGame();
    QString getPlaceMod();

    void startReadParameters();
    void updateParameters();



public slots:
    void themeDialogOpen();
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

    void greatBUTTON();

};
#endif // MAINWINDOW_H
