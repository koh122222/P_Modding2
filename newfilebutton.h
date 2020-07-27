#ifndef NEWFILEBUTTON_H
#define NEWFILEBUTTON_H

#include <QPushButton>
#include <QString>
#include "maineditor.h"

class NewFileButton : public QPushButton
{
    Q_OBJECT

public:
    NewFileButton(QString name,QWidget* parent);
    void resizeGeometryEvent();

};

#endif // NEWFILEBUTTON_H
