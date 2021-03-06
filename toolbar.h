#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QAction>
#include <QVector>

class ToolBar : public QToolBar
{
    Q_OBJECT
public:
    QVector<QAction*> allActionButton;
    enum TOOL_ACTION
    {
        NEW_FILE,
        OPEN_FILE,
        SAVE_FILE,
        SAVE_ALL_FILE,
        CLOSE_FILE,
        CLOSE_ALL_FILE, ///////RASDELITEL
        COPY_TEXT,
        CUT_TEXT,
        PASTE_TEXT,
        BACK_TEXT,
        FORWARD_TEXT,
        FIND_TEXT,
        REPLACE_WORD,
        INCREASE_TEXT,
        REDUCE_TEXT,
        GREAT_BUTTON
    };
    ToolBar(QWidget *parent);
};

#endif // TOOLBAR_H
