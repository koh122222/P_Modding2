#include "maineditor.h"

MainEditor::MainEditor(QWidget *parent) : QWidget(parent)
{
    //showMaximized();
    secondTextEdit = new QTextEdit("right", this);
    QTextEdit *threeTextEdit = new QTextEdit("three", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(secondTextEdit, 33);
    layout->addWidget(threeTextEdit, 50);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(1);

}
