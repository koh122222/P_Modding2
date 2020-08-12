#include "toolbar.h"

ToolBar::ToolBar(QWidget* parent)
    :QToolBar(parent)
{
    addAction(QIcon("://resources//toolIcon//icon_save.png"), "save (Crtl + S)");
    //://resources//
}
