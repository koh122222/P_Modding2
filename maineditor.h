#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTabWidget>
#include <unordered_map>
#include "codeeditor.h"

using AllOpenFile = std::unordered_map<QString, CodeEditor*>;

class MainEditor : public QWidget
{
    Q_OBJECT
    QTabWidget *fileEditor;
    AllOpenFile allOpenFile;
    QVBoxLayout *layout;
    QFont *nowFont;
public:
    explicit MainEditor(QWidget *parent = nullptr);

    void openFile(QString &path);

    void setFont(QFont* newFont);

signals:

public slots:
    void closeFile(qint32 index);

};

#endif // MODEDITOR_H
