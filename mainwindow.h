#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QString>
#include "gamefiles.h"
#include "maineditor.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
    QString placeGame;
    QString placeMod;
public:
    GameFiles* gameFiles;
    MainEditor* mainEditor;



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
};
#endif // MAINWINDOW_H
