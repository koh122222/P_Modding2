#include "gamefiles.h"
#include <QDebug>
GameFiles::GameFiles(QWidget *parent) : QWidget(parent)
{
    firstTextEdit = new QTextEdit("l", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(firstTextEdit);
    layout->setContentsMargins(0,0,0,0);
    //setLayout(layout);

}
