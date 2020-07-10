#ifndef GAMEFILES_H
#define GAMEFILES_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>

class GameFiles : public QWidget
{
    Q_OBJECT
    QSplitter *splitter;
    QFileSystemModel *fileModel;
    QTreeView *mainTree;
    QTreeView *favouritesTree;
    QTextEdit *firstTextEdit;
public:
    explicit GameFiles(QWidget *parent = nullptr);

signals:

};

#endif // GAMEFILES_H
