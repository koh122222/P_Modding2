#ifndef ONLYFILESYSTEMMODEL_H
#define ONLYFILESYSTEMMODEL_H
#include <QFileSystemModel>
#include <QString>
class onlyFileSystemModel : public QFileSystemModel
{
    QString firstName = "Folder";
public:
    onlyFileSystemModel(QObject *parent = nullptr);
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void setFirstName(QString name);
};

#endif // ONLYFILESYSTEMMODEL_H
