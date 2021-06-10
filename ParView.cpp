#include "ParView.h"

ParView::ParView(QWidget *parent) : QWidget(parent)
{
    parType = new QComboBox(this);
    findPar = new QLineEdit(this);
    seePar = new QTreeView(this);


    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(parType, 0, 0, 1, 10);
    layout->addWidget(findPar, 1, 0, 1, 10);
    layout->addWidget(seePar, 2, 0, 1, 10);

}

QString ParView::getParType()
{//add if not comlite
    return parType->currentText();
}
QString ParView::getFindPar()
{
    return findPar->text();
}
