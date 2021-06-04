#ifndef MODIF_VIEW_H
#define MODIF_VIEW_H
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <QPushButton>
#include "vector"
#include "primparseryaml.h"

class ModifView : public QWidget
{
    Q_OBJECT
    QGridLayout* layout;
    QTextEdit* testEditor;

    QCheckBox* allFilter;
    QCheckBox* textFilter;
    QCheckBox* tagFilter;
    QCheckBox* eventFilter;
    QCheckBox* modifierFilter;
    QPushButton* opener;

    QString currentText;

public:
    ModModel* allMap;
    ModModel* textMap;
    ModModel* tagMap;
    ModModel* eventMap;
    ModModel* modifierMap;

    std::vector <QString> modifiers;

    std::vector<QString> multiOpener(int levelZone, QString fileAdd, std::vector<QString> keys);
    explicit ModifView(QWidget *parent = nullptr);
    bool messagePoint (QString localizetedText);
    bool tagPoint (QString programText);
    bool adj_tagPoint (QString programText);
    bool eventPoint (QString programText);
    void localOpener();
    void ideasOpen ();
    void ageOpener ();
    void opener2();
    void opener3();
public slots:
    void allPrint(int a);
    void textPrint(int a);
    void tagPrint(int a);
    void eventPrint(int a);
    void modifierPrint(int a);
    void modifierOpener();
signals:

};

#endif // MODIF_VIEW_H
