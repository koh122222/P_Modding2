#ifndef WORKWINDOW_H
#define  WORKWINDOW_H

#include <QObject>
#include <QWidget>
#include <QComboBox>
#include <QToolBar>
#include <QLabel>
#include <QGridLayout>
#include <QTextEdit>
#include <QToolButton>
#include <QVector>
#include <QStackedWidget>
#include <QMap>
#include "codeeditor.h"
#include "allpar.h"

using FullName = QString;

class WorkWindow : public QWidget
{
    Q_OBJECT
    QComboBox *openEdit;
    QToolButton *delButton;
    QComboBox *subTypesFile;
    QVector<std::pair<FullName, CodeEditor*>> workFiles;
    QStackedWidget* stackedWidget;

public:
    WorkWindow(QWidget* parent = nullptr);

    bool setEditor(QString fullFile);
    bool addEditor(QString openFile, FileSystem fileSystem, QFont* font);
    CodeEditor* getEditor(QString findFullName);
    CodeEditor* getCurrentEditor();
    //void addEditor(FileEditor* newEditor)
};

#endif // WORKWINDOW_H
