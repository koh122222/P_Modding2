#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTabWidget>
#include <QPushButton>
#include <unordered_map>
#include "tabeditor.h"
#include "codeeditor.h"
#include "createcopynewfiledialog.h"

class NewFileButton;

using AllOpenFile = std::unordered_map<QString, CodeEditor*>;

class MainEditor : public QWidget
{
    Q_OBJECT
    TabEditor *fileEditor;
    NewFileButton *createFileModButton;
    AllOpenFile allOpenFile;
    QVBoxLayout *layout;
    QFont *nowFont;


    CreateCopyNewFileDialog* createCopyNewFileDialog;
public:
    explicit MainEditor(QWidget *parent = nullptr);
    enum FileSystem
    {
        GAME_FILE,
        MOD_FILE
    };

    void openTextFile(QString &path, FileSystem fileSystem);
    void setFont(QFont* newFont);
protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    void closeFile(qint32 index);
    void changeTab(qint32 index);
    void createFileMod();
    void createIncludeFileMod();

};

#endif // MODEDITOR_H
