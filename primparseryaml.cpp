#include "primparseryaml.h"
#include <QTextStream>
#include <QDebug>
void YAML::reedFile(QString adress, ModModel& strMap)
{
    qDebug() << "start reed " + adress;
    QFile file(adress);
    file.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&file);
    if (!in.atEnd())
        in.readLine(); //for continue first str
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if (line.size() == 0)
            continue;
        qint32 startStr = line.indexOf("\"");
        strMap.insert(ModModel::value_type(line.mid(1, line.indexOf(" ", 1) - 1), //code name
                                                 line.mid(startStr + 1, line.indexOf("\"", startStr + 1) - startStr - 1))); //realy name
    }
    file.close();
}

void writeFile(QString adress, ModModel& strMap)
{
    QFile file(adress);
    file.open(QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    out << adress.mid(adress.lastIndexOf('/'), adress.lastIndexOf('.')) + ":\n";
    for (auto &c : strMap)
    {
        out << " " << c.first << " \"" << c.second << "\"";
    }
    file.close();
}

