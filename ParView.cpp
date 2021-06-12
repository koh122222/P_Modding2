#include "ParView.h"

ParView::ParView(QWidget *parent) : QWidget(parent)
{
    parViewFilterModel = new ParViewSortFilterProxyModel(this);
    parType = TYPE_MOD::M_START_TYPE;
    parCode = new QComboBox(this);
    findPar = new QLineEdit(this);
    seePar = new QTreeView(this);

    for (auto c : AllPar::typeModString)
    {
        parCode->addItem(c);
    }
    //QComboBox::currentTextChanged()

    connect(parCode, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setParType()));
    connect(findPar, &QLineEdit::textChanged,
            parViewFilterModel, &ParViewSortFilterProxyModel::invalidate);
    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(parCode, 0, 0, 1, 10);
    layout->addWidget(findPar, 1, 0, 1, 10);
    layout->addWidget(seePar, 2, 0, 1, 10);

}

void ParView::setParType()
{
    qDebug("setParType");
    QString nowParCode = getParCode();
    for (int i = 0; i < AllPar::typeModString.size(); ++i)
    {
        if (AllPar::typeModString[i] == nowParCode)
        {
            parType = static_cast<TYPE_MOD>(i);
            break;
        }
    }
    setParType(parType);
}

void ParView::setParType(TYPE_MOD newTypeMod)
{
    parType = newTypeMod;
    parViewFilterModel->setSourceModel(&AllPar::modVector[parType]);
    seePar->setModel(parViewFilterModel);
}

TYPE_MOD ParView::getParType()
{
    return parType;
}

QString ParView::getParCode()
{//add if not comlite
    return parCode->currentText();
}
QString ParView::getFindPar()
{
    return findPar->text();
}
