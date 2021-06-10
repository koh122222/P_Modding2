#ifndef PARVIEWSORTFILTERPROXYMODEL_H
#define PARVIEWSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class ParViewSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    ParViewSortFilterProxyModel(QObject *parent = nullptr);
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;

};

#endif // PARVIEWSORTFILTERPROXYMODEL_H
