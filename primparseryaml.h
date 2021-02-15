#ifndef PRIMPARSERYAML_H
#define PRIMPARSERYAML_H
#include <QFile>
#include <unordered_map>
#include <QHash>
#include "allpar.h"

namespace YAML
{
    void reedFile(QString adress, localMap& strMap);
    void writeFile(QString adress, localMap& strMap);
}

#endif // PRIMPARSERYAML_H




