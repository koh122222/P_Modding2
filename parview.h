#ifndef PARVIEW_H
#define PARVIEW_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QTreeView>
#include <QLineEdit>
#include <QGridLayout>
#include "allpar.h"
#include "parviewsortfilterproxymodel.h"

class ParView : public QWidget
{
    Q_OBJECT
    ParViewSortFilterProxyModel* parViewFilterModel;
    TYPE_MOD parType;
    QComboBox* parCode;
    QLineEdit* findPar;
    QTreeView* seePar;
public:
    explicit ParView(QWidget *parent = nullptr);

    void setParType(TYPE_MOD newTypeMod);
    TYPE_MOD getParType();
    QString getParCode();
    QString getFindPar();
signals:

public slots:
    void setParType();

};

#endif // PARVIEW_H
