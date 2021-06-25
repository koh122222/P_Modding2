#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QTabWidget>
#include <QPushButton>
#include <unordered_map>
#include <QMainWindow>
#include <QDockWidget>
#include <QVector>
#include "tabeditor.h"
#include "codeeditor.h"
#include "createcopynewfiledialog.h"
#include "workWindow.h"
#include "allpar.h"

class NewFileButton;

using AllOpenFile = std::unordered_map<QString, CodeEditor*>;
//#define nowCodeEditor static_cast<CodeEditor*>(fileEditor->currentWidget());

class MainEditor : public QMainWindow
{
    Q_OBJECT
    QWidget* centralWidget;
    QVector<WorkWindow*> savedWorkWindows;
    QDockWidget *dock;
    QWidget* nowFileEditor = nullptr;
    QVector<std::pair<QString, QVector<CodeEditor*>>> multiCodeEditor; //name editor's file, vector of them Editor

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

    void openTextFile(QString &path, FileSystem fileSystem);
    void setFont(QFont* newFont);
    QFont* getFont();
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


    void updateAllHighlighter();
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

    void seeOldWindow(QWidget* oldW, QWidget* newW);

};

#endif // MODEDITOR_H
