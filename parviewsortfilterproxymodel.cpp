#include "parviewsortfilterproxymodel.h"
#include "ParView.h"
#include "allpar.h"
#include <QDebug>
ParViewSortFilterProxyModel::ParViewSortFilterProxyModel(QObject *parent)
    :QSortFilterProxyModel(parent)
{

}

bool ParViewSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QString findPar =
            static_cast<ParView*>(parent())->getFindPar();
    QString nowPar = sourceModel()->index(source_row, 0).data().toString();
    QString nowParTranslate = sourceModel()->index(source_row, 1).data().toString();
    if (findPar == "")
        return true;
    else
        return (nowPar.indexOf(findPar) != -1) || (nowParTranslate.indexOf(findPar) != -1);// &&
            //source_parent.data().value<ModPair>().first.indexOf(nowFindPar));



    return true;
}
