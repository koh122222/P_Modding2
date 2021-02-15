#ifndef MODMODEL_H
#define MODMODEL_H
#include <QAbstractItemModel>
#include <QString>
#include <vector>
#include <QModelIndex>
#include <algorithm>

using ModPair = std::pair<QString, QString>;

class ModModel : public QAbstractTableModel
{
    Q_OBJECT
    std::vector<ModPair> items;
public:
    ModModel();
private:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void sort(int column = 0, Qt::SortOrder order = Qt::AscendingOrder);

public:
    QString getCodeName(QString& findLName);
    QString getLanguageName(QString& findCName);

    bool insertMod(ModPair pMod);
    bool eraseMod(ModPair pMod);
};

#endif // MODMODEL_H
