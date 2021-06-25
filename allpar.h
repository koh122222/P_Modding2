#ifndef ALLPARAMETERS_H
#define ALLPARAMETERS_H
#include <array>
#include <QColor>
#include <unordered_map>
#include <QVector>
#include "highlighter.h"
#include "modmodel.h"

using gameModif = std::vector<ModModel>;

class MainWindow;

//after add type_mod, add string in typeModString
enum TYPE_MOD
{
    M_START_TYPE,
    M_EU_BEGIN,
    M_EU_IDEAS,
    M_EU_EVENTS,
    M_EU_END,
    M_END_TYPE
};

enum FileSystem
{
    FS_GAME_FILE,
    FS_MOD_FILE
};


class AllPar
{
public:
    
static MainWindow* mObject;

static std::array<QString, TYPE_MOD::M_END_TYPE> typeModString;

static std::array<QColor, TYPE_MOD::M_END_TYPE> highlighter_light;

static std::unordered_map<QString, QString> allGameBase;

static gameModif modVector;

static std::map<QString /*type colors*/,
    std::unordered_map<QString, QString>> interface_colors;



};
#endif // ALLPARAMETERS_H
