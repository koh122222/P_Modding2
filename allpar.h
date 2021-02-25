#ifndef ALLPARAMETERS_H
#define ALLPARAMETERS_H
#include <array>
#include <QColor>
#include <unordered_map>
#include "highlighter.h"
#include "modmodel.h"

using gameModif = std::vector<ModModel>;

enum TYPE_MOD
{
    M_EU_BEGIN,
    M_EU_IDEAS,
    M_EU_EVENTS,
    M_EU_END,
    M_END_TYPE
};

class AllPar
{
public:

static std::array<QColor, TYPE_MOD::M_END_TYPE> highlighter_light;

static std::unordered_map<QString, QString> allGameBase;

static gameModif modVector;


enum TYPE_VIEW_THEME
{
    VT_DARK
};

static std::vector<std::unordered_map<QString, QString>> interface_colors;



};
#endif // ALLPARAMETERS_H
