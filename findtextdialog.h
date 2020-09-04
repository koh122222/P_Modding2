#ifndef FINDTEXTDIALOG_H
#define FINDTEXTDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QTabWidget>
#include <QPushButton>



class FindTextWidget : public QWidget
{
    Q_OBJECT
    QLabel* findLabel;
    QComboBox* findNameEditBox;
    QPushButton* upFindButton;
    QPushButton* downFindButton;
    QPushButton* countButton;
    QPushButton* findNowDocButton;
    QPushButton* findAllDocButton;
    QPushButton* closeButton;
    QCheckBox* matchWholeWordOnlyBox;
    QCheckBox* matchCaseBox;

public:
    FindTextWidget(QWidget* parent);
    QString getFindName();
    void addFindName(QString addName);
    void setFindName(QString setName);
    bool isFind(QString findText);
    void countText();
    void findName(bool isDown);



public slots:
    void findNameDown();
    void findNameUp();

};

class RenameTextWidget : public QWidget
{
    QLabel* findLabel;
    QComboBox* findNameEditBox;
    QComboBox* reNameEditBox;
    QPushButton* upFindButton;
    QPushButton* downFindButton;
    QPushButton* renameButton;
    QPushButton* renameAllButton;
    QPushButton* renameAllDocButton;
    QPushButton* closeButton;
    QCheckBox* matchWholeWordOnlyBox;
    QCheckBox* matchCaseBox;
public:
    RenameTextWidget(QWidget* parent);
    QString getFindName();
    QString getReName();
    void addFindName(QString addName);
    void addReName(QString addName);
    void setFindName(QString setName);

    bool isFind(QString findText);

};


class FindTextDialog : public QDialog
{
    Q_OBJECT
    QTabWidget* tabWidget;
    FindTextWidget* findTextWidget;
    RenameTextWidget* renameTextWidget;
public:
    FindTextDialog(QWidget* parent);
    void startWork();
public slots:
    void changeTab(int);
};

#endif // FINDTEXTDIALOG_H
