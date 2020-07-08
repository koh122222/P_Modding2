#ifndef MAINEDITOR_H
#define MAINEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>

class MainEditor : public QWidget
{
    Q_OBJECT
    QTextEdit *secondTextEdit;
public:
    explicit MainEditor(QWidget *parent = nullptr);

signals:

};

#endif // MODEDITOR_H
