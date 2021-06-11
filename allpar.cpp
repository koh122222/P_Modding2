#include "allpar.h"

MainWindow* AllPar::mObject = nullptr;

std::array<QString, TYPE_MOD::M_END_TYPE> AllPar::typeModString
{
    "m_START_TYPE",
    "m_eu_begin", //M_EU_BEGIN
    "eu_ideas",
    "eu_event",
    "m_EU_END",
};

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

std::map<QString, std::unordered_map<QString, QString>> AllPar::interface_colors
{
    {
        QString("Dark Theme")
    ,
    {//DARK
        {QStringLiteral("mainBGColor"), QStringLiteral("#2e2f30")},
        {QStringLiteral("secondBGColor"), QStringLiteral("#404142")},
        {QStringLiteral("selectBGColor"), QStringLiteral("#5e5f60")},
        {QStringLiteral("selectBGColor2"), QStringLiteral("#1d545c")},
        {QStringLiteral("mainTextColor"), QStringLiteral("#d0d0d0")},
        {QStringLiteral("lightBorderColor"), QStringLiteral("#121212")},
        {QStringLiteral("lightBorderColor2"), QStringLiteral("#303030")},
        {QStringLiteral("lightBorderColor3"), QStringLiteral("#666768")},
        {QStringLiteral("scrollHandle"), QStringLiteral("#505051")}

    }
    }
};

