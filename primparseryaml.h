#ifndef PRIMPARSERYAML_H
#define PRIMPARSERYAML_H
#include <QFile>
#include <unordered_map>
#include <QHash>

using localMap = QHash<QString, QString>;

namespace YAML
{
    void reedFile(QString adress, localMap& strMap);
}

#endif // PRIMPARSERYAML_H




