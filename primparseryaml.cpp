#include "primparseryaml.h"
#include <QTextStream>
#include <QDebug>
void YAML::reedFile(QString adress, localMap& strMap)
{
    QFile file(adress);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    if (!in.atEnd())
        in.readLine(); //for continue first str
    while (!in.atEnd())
    {
        QString line = in.readLine();
        //qDebug()<<line;
        if (line.size() == 0)
            continue;
        qint32 startStr = line.indexOf("\"");
        strMap.insert(localMap::value_type(line.mid(1, line.indexOf(" ", 1) - 1), //code name
                                                 line.mid(startStr + 1, line.indexOf("\"", startStr + 1) - startStr - 1))); //realy name
    }
    file.close();
}
