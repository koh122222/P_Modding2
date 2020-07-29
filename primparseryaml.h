#ifndef PRIMPARSERYAML_H
#define PRIMPARSERYAML_H
#include <QFile>
#include <unordered_map>

using localMap = std::unordered_map<QString, QString>;

namespace YAML
{
    void reedFile(QString adress, localMap& strMap);
}

#endif // PRIMPARSERYAML_H




