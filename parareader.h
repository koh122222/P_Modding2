#ifndef PARAREADER_H
#define PARAREADER_H
#include <QObject>
#include <QString>
#include <QVector>
#include <QTextStream>
#include "modmodel.h"
#include "allpar.h"

class paraReader : public QObject
{

    Q_OBJECT
    QString gamepath;
public:
    paraReader(QObject * parent);
    QVector <QString> modReader();
    ModModel model_maker(QVector <QString> codename);

};

#endif // PARAREADER_H
