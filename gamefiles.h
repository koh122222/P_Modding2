#ifndef GAMEFILES_H
#define GAMEFILES_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class GameFiles : public QWidget
{
    Q_OBJECT
    QTextEdit *firstTextEdit;
public:
    explicit GameFiles(QWidget *parent = nullptr);

signals:

};

#endif // GAMEFILES_H
