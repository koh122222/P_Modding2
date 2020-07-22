#include "maineditor.h"
#include "QTextStream"
#include "QMessageBox"
#include <QDebug>
MainEditor::MainEditor(QWidget *parent) : QWidget(parent)
{
    //showMaximized();
    //layout->addWidget(secondTextEdit, 33);
    //layout->addWidget(threeTextEdit, 50);
    fileEditor = new CodeEditor(this);
    QFont fontEditor("Courier", 16);
    fileEditor->setFont(fontEditor);
    QFontMetrics metrics(fontEditor);
    fileEditor->setTabStopDistance(metrics.horizontalAdvance("    "));

    layout = new QVBoxLayout(this);
    layout->addWidget(fileEditor);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(1);
    fileEditor->setPlainText("1234567");


}

void MainEditor::openFiles(QString &path)
{
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    fileEditor->setPlainText(text);
    file.close();
}
