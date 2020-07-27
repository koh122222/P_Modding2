#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QStyleOption>
#include <QStylePainter>
#include <QTabWidget>


class TabEditor : public QTabWidget
{
    Q_OBJECT
public:
    TabEditor(QWidget *parent = nullptr);
};

#endif // TEXTEDITOR_H
