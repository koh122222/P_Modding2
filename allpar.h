#ifndef ALLPARAMETERS_H
#define ALLPARAMETERS_H
#include <array>
#include <QColor>
#include <unordered_map>
#include "highlighter.h"
#include "modmodel.h"

using localMap = std::unordered_map<QString, QString>;
using gameModif = std::vector<localMap>;

enum TYPE_MOD
{
    EU_BEGIN,
    EU_IDEAS,
    EU_EVENTS,
    EU_END,
    END_TYPE
};

class AllPar
{
public:

static std::array<QColor, TYPE_MOD::END_TYPE> highlighter_light;

static std::unordered_map<QString, QString> allGameBase;

static gameModif modVector;


};




#endif // ALLPARAMETERS_H
