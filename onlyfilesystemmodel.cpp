#include "onlyfilesystemmodel.h"

onlyFileSystemModel::onlyFileSystemModel(QObject *parent)
    :QFileSystemModel(parent)
{

}

QVariant onlyFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{

    if ((section == 0) && (role == Qt::DisplayRole) && (orientation == Qt::Horizontal))
    {
        return firstName;
    } else {
        return QFileSystemModel::headerData(section, orientation, role);
    }
}

void onlyFileSystemModel::setFirstName(QString name)
{
    firstName = name;
}
