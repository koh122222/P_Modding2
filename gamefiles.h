#ifndef GAMEFILES_H
#define GAMEFILES_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QModelIndex>
#include <QMainWindow>
#include <onlyfilesystemmodel.h>
#include "maineditor.h"

class GameFiles : public QWidget
{
    Q_OBJECT

    QVBoxLayout *layout;
    QSplitter *splitter;

    onlyFileSystemModel *fileModel;
    onlyFileSystemModel *favouritesModel;

    QTreeView *mainTree;
    QTreeView *favouritesTree;
public:
    explicit GameFiles(QWidget *parent = nullptr);

    void setGamePlace(QString placeGame);
    void setModPlace(QString placeMod);

    void openFileFromTree(const QModelIndex& index, MainEditor::FileSystem fileSystem);

signals:

public slots:
    void openFileFromTreeGame(const QModelIndex& index);
    void openFileFromTreeMod(const QModelIndex& index);



};

#endif // GAMEFILES_H
