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
    QString findName;
    qint32 countFindName;


    //////////////////////////////////////////////////
    CodeEditor *currentEditor = nullptr;


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
    void saveAllFile();
    void saveFile();
    void saveFile(CodeEditor* saveEditor);
    void closeAllFile();
    void closeFile();
    void copyText();
    void cutText();
    void pasteText();
    void backText();
    void forwardText();



    qint32 lighterFindText(QString fText, bool down);




    //void closeFile(CodeEditor* saveEditor);
protected:
    void resizeEvent(QResizeEvent *event) override;

signals:

public slots:
    bool closeFile(qint32 index);
    void changeTab(qint32 index);
    void createFileMod();
    void createIncludeFileMod();
    int returnCountText(QString cText, bool matchWhileWordOnly,
                           bool matchCase);

};

#endif // MODEDITOR_H
