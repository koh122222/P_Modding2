#ifndef MODIF_VIEW_H
#define MODIF_VIEW_H
#include <QWidget>

class ModifView : public QWidget
{
    Q_OBJECT
public:
    explicit ModifView(QWidget *parent = nullptr);
    bool messagePoint (QString localizetedText);
    bool tagPoint (QString programText);
    bool adj_tagPoint (QString programText);
signals:

};

#endif // MODIF_VIEW_H
