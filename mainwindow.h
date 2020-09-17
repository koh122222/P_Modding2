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
#include "findtextdialog.h"

namespace TYPE_MOD {
    enum EU {
        IDEAS,
        EVENTS
    };
}



using ModMap = std::vector<std::pair<TYPE_MOD::EU, localMap>>;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString gameName;

    QDir *dirProgram;
    QDir *placeGame;
    QDir *placeMod;

    ModMap* modMap;


public:

    static std::unordered_map<QString, QString>  allGameBase;

    ToolBar* toolBar;
    GameFiles* gameFiles;
    MainEditor* mainEditor;
    ModifView* modifView;

    FindTextDialog* textFinder;
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

    void slotPress_ctrlC(); // there is no direct keyboard binding
    void slotPress_ctrlX(); // there is no direct keyboard binding
    void slotPress_ctrlV(); // there is no direct keyboard binding
    void slotPress_ctrlZ(); // there is no direct keyboard binding
    void slotPress_ctrlY(); // there is no direct keyboard binding
    void slotPress_ctrlF();

    void setStyle();

};
#endif // MAINWINDOW_H
