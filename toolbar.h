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
    enum TOOL_ACTION
    {
        NEW_FILE,
        OPEN_FILE,
        SAVE_FILE,
        SAVE_ALL_FILE,
        CLOSE_FILE,
        CLOSE_ALL_FILE, ///////RASDELITEL
        COPY_TEXT

    };
    ToolBar(QWidget *parent);
};

#endif // TOOLBAR_H
