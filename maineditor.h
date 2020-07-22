#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <codeeditor.h>

class MainEditor : public QWidget
{
    Q_OBJECT
    CodeEditor *fileEditor;
    QVBoxLayout *layout;
public:
    explicit MainEditor(QWidget *parent = nullptr);

    void openFiles(QString &path);

signals:

public slots:

};

#endif // MODEDITOR_H
