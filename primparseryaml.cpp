#include "primparseryaml.h"
#include <QTextStream>
void YAML::reedFile(QFile* file, twoMap& strMap)
{
    QTextStream in(file);
    if (!in.atEnd())
        in.readLine(); //for continue first str
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.size() == 0)
            continue;
        qint32 startStr = line.indexOf("\"");
        strMap.insert(twoMap::value_type(line.mid(1, line.indexOf(" ", 1) - 1), //code name
                                         line.mid(startStr + 1, line.indexOf("\"", startStr + 1) - startStr - 1))); //realy name

    }
}
