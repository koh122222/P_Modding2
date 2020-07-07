#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QVBoxLayout>

#include "gamefiles.h"
#include "maineditor.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

    GameFiles* gameFiles;
    MainEditor* mainEditor;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
