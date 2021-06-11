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
    TYPE_MOD enumParType = TYPE_MOD::M_START_TYPE;
    for (int i = 0; i < AllPar::typeModString.size(); ++i)
    {
        if (AllPar::typeModString[i] == nowParType)
        {
            enumParType = static_cast<TYPE_MOD>(i);
            break;
        }
    }


//QString nowFindPar =
           // static_cast<ParView*>(parent())->getFindPar();

    //return (nowParType )


    return true;
}
