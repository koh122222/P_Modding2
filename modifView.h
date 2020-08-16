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
    QCheckBox* textFilter;
    QCheckBox* tagFilter;
    QCheckBox* testFilter;

    QString currentText;
public:
    localMap* allMap;
    localMap* textMap;
    localMap* tagMap;
    localMap* eventMap;

    explicit ModifView(QWidget *parent = nullptr);
    bool messagePoint (QString localizetedText);
    bool tagPoint (QString programText);
    bool adj_tagPoint (QString programText);
    bool eventPoint (QString programText);
    void localOpener();
public slots:
    void allPrint(int a);
    void textPrint(int a);
    void tagPrint(int a);
    void testPrint(int a);
signals:

};

#endif // MODIF_VIEW_H
