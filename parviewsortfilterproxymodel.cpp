#include "parviewsortfilterproxymodel.h"
#include "ParView.h"
#include "allpar.h"

ParViewSortFilterProxyModel::ParViewSortFilterProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{

}

bool ParViewSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QString nowParType =
            static_cast<ParView*>(parent())->getParType();
    for (int i = 0; i < AllPar::typeModString.size(); ++i)
    {

    }
    TYPE_MOD enumParType =
QString nowFindPar =
            static_cast<ParView*>(parent())->getFindPar();
    return (nowParType == AllPar::)


    return true;
}
