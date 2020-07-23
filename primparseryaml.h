#ifndef PRIMPARSERYAML_H
#define PRIMPARSERYAML_H
#include <QFile>
#include <unordered_map>

using twoMap = std::unordered_map<QString, QString>;

namespace YAML
{
    void reedFile(QFile* file, twoMap& strMap);
}

#endif // PRIMPARSERYAML_H




