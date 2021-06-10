#ifndef PARVIEW_H
#define PARVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTreeView>
#include <QLineEdit>
#include <QGridLayout>

class ParView : public QWidget
{
    Q_OBJECT
    QComboBox* parType;
    QLineEdit* findPar;
    QTreeView* seePar;
public:
    explicit ParView(QWidget *parent = nullptr);

    QString getParType();
    QString getFindPar();
signals:

};

#endif // PARVIEW_H
