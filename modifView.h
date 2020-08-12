#ifndef MODIF_VIEW_H
#define MODIF_VIEW_H
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QCheckBox>
#include "primparseryaml.h"

class ModifView : public QWidget
{
    Q_OBJECT
    QGridLayout* layout;
    QTextEdit* testEditor;

    QCheckBox* allFilter;
public:
    localMap* allMap;
    explicit ModifView(QWidget *parent = nullptr);
    bool messagePoint (QString localizetedText);
    bool tagPoint (QString programText);
    bool adj_tagPoint (QString programText);
    void localOpener();
public slots:
    void allPrint(int a);
signals:

};

#endif // MODIF_VIEW_H
