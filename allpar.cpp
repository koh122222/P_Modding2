#include "allpar.h"

std::array<QColor, TYPE_MOD::M_END_TYPE> AllPar::highlighter_light
{
    QColor{}, //EU_BEGIN
    QColor{70, 99, 41}, //EU_IDEAS
    QColor{54, 78, 127}, //EU_EVENTS
    QColor{} //EU_END

};

std::unordered_map<QString, QString> AllPar::allGameBase
{
    {QStringLiteral("Europa Universalis IV"), QStringLiteral("eu4")}
};

gameModif AllPar::modVector
{

};

std::vector<std::unordered_map<QString, QString>> AllPar::interface_colors
{
    {//DARK
        {QStringLiteral("mainColor"), QStringLiteral("#363636")},
        {QStringLiteral("lightBorderColor"), QStringLiteral("#121212")}
    }
};
