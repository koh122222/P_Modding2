#ifndef PRIMPARSERYAML_H
#define PRIMPARSERYAML_H
#include <QFile>
#include <unordered_map>
#include <QHash>
#include "allpar.h"

namespace YAML
{
    void reedFile(QString adress, ModModel& strMap);
    void writeFile(QString adress, ModModel& strMap);
}

#endif // PRIMPARSERYAML_H




