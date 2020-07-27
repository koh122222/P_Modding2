#include "newfilebutton.h"
#include <QDebug>

NewFileButton::NewFileButton(QString name,QWidget *parent)
    :QPushButton(name, parent)
{

}

void NewFileButton::resizeGeometryEvent()
{
    QRect cr = static_cast<MainEditor*>(parent())->contentsRect();
    setGeometry(QRect(cr.right() - 150, cr.top() + 26, 130, 30));
}
