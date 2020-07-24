#include "maineditor.h"
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QString>

MainEditor::MainEditor(QWidget *parent) : QWidget(parent)
{
    fileEditor = new QTabWidget(this);
    fileEditor->setTabsClosable(true);
    //fileEditor->addTab(new CodeEditor, "default");



    layout = new QVBoxLayout(this);
    layout->addWidget(fileEditor);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);
    /*
    fileEditor = new CodeEditor(this);
    QFont fontEditor("Courier", 16);
    fileEditor->setFont(fontEditor);
    QFontMetrics metrics(fontEditor);
    fileEditor->setTabStopDistance(metrics.horizontalAdvance("    "));
*/


}

void MainEditor::openFile(QString &path)
{
    auto c = allOpenFile.find(path);
    if (c != allOpenFile.end()) //if the tab exists
    {
        fileEditor->setCurrentWidget(c->second);
    }
    else //create new Tab
    {
        CodeEditor* newCodeEditor = new CodeEditor;
        QFile file(path);

        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        newCodeEditor->setPlainText(text);
        file.close();
        allOpenFile.insert(AllOpenFile::value_type(path, newCodeEditor));
        fileEditor->addTab(newCodeEditor,
                           path.mid(path.lastIndexOf("/") + 1));


    }



            /*for_each(,[path](CodeEditor* element) -> bool
    {
        return true;

    });*/
    /*
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    fileEditor->setPlainText(text);
    file.close();
    */
}
