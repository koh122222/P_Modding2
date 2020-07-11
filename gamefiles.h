#ifndef GAMEFILES_H
#define GAMEFILES_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>

class GameFiles : public QWidget
{
    Q_OBJECT
    QVBoxLayout *layout;
    QSplitter *splitter;

    QFileSystemModel *fileModel;
    QFileSystemModel *favouritesModel;

    QTreeView *mainTree;
    QTreeView *favouritesTree;
public:
    explicit GameFiles(QWidget *parent = nullptr);

signals:

public slots:
    void openFiles(const QModelIndex& index);


};

#endif // GAMEFILES_H
