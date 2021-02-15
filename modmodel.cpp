#include "modmodel.h"
#include <QDebug>

ModModel::ModModel()
{
}

ModModel::ModModel(const ModModel& copyEl)
{
    qDebug() << "COPY MODMODEL " << copyEl.items[0].first;
    items = copyEl.items;
}

ModModel& ModModel::operator=(const ModModel& copyEl)
{
    qDebug() << "COPY MODMODEL2 " << copyEl.items[0].first;
    if (this == &copyEl)
        return *this;
    items = copyEl.items;
    return *this;
}
int ModModel::rowCount(const QModelIndex &parent) const
{
    return items.size();
}

int ModModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}
QVariant ModModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
            return QVariant(items[index.row()].first);
        else
            return QVariant(items[index.row()].second);
    }
    return QVariant();
}

Qt::ItemFlags ModModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

void ModModel::sort(int column, Qt::SortOrder orde)
{
    std::sort(items.begin(), items.end(), []
              (const ModPair &lhs,
              const ModPair &rhs)
    { return lhs.first < rhs.first; });
}

ModPair* ModModel::begin()
{
    return &*(items.begin());
}

ModPair* ModModel::end()
{
    return &*(items.end());
}

QString ModModel::getCodeName(QString& findLName)
{
    auto needPair = std::lower_bound(items.begin(), items.end(), findLName, []
                            (const ModPair &el, const QString el2)
    { return el.second < el2; });
    if (needPair != items.end() && needPair->second == findLName)
        return needPair->first;
    else
        return QString("PM_THE_ELEMENT_WILL_NOT_FIND");
}

QString ModModel::getLanguageName(QString& findCName)
{
    auto needPair = std::lower_bound(items.begin(), items.end(), findCName, []
                            (const ModPair &el, const QString el2)
    { return el.first < el2; });
    if (needPair != items.end() &&
            needPair->first == findCName)
        return needPair->second;
    else
        return QString("PM_THE_ELEMENT_WILL_NOT_FIND");
}

bool ModModel::insert(ModPair pMod)
{
    auto startPair = std::lower_bound(items.begin(), items.end(), pMod);
    items.insert(startPair, pMod);
    return true;
}

bool ModModel::erase(ModPair pMod)
{
    auto delPair = std::lower_bound(items.begin(), items.end(), pMod);
    if (*delPair == pMod)
    items.erase(delPair);
    return true;
}

std::vector<ModPair>& ModModel::mainItems()
{
    return items;
}
