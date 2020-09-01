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

class MainFinder : public QWidget
{
    Q_OBJECT
public:
    MainFinder(QWidget* parent);
};

class FindTextWidget : public MainFinder
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
    QCheckBox* findFullNameBox;
    QCheckBox* findWithReg;

public:
    FindTextWidget(QWidget* parent);

};



class FindTextDialog : public QDialog
{
    Q_OBJECT
    QTabWidget* tabWidget;
    FindTextWidget* findTextWidget;
public:
    FindTextDialog(QWidget* parent);
};

#endif // FINDTEXTDIALOG_H
