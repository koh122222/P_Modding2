#ifndef MODIF_VIEW_H
#define MODIF_VIEW_H
#include <QWidget>
#include <QTextEdit>
#include <QGridLayout>


class ModifView : public QWidget
{
    Q_OBJECT
    QGridLayout* layout;
    QTextEdit* testEditor;
public:
    explicit ModifView(QWidget *parent = nullptr);
    bool messagePoint (QString localizetedText);
    bool tagPoint (QString programText);
    bool adj_tagPoint (QString programText);
    void localOpener();
signals:

};

#endif // MODIF_VIEW_H
