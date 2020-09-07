#include "findtextdialog.h"
#include "mainwindow.h"
#include <QDebug>

FindTextWidget::FindTextWidget(QWidget* parent)
    :QWidget(parent)
{
    findLabel = new QLabel("Find: ", this);
    findNameEditBox = new QComboBox(this);
    findNameEditBox->setEditable(true);
    upFindButton = new QPushButton("up", this);
    upFindButton->setMaximumWidth(30);
    downFindButton = new QPushButton("Find next", this);
    downFindButton->setMaximumWidth(80);
    countButton = new QPushButton("count", this);
    countButton->setMaximumWidth(120);
    findNowDocButton = new QPushButton("find in this Doc", this);
    findNowDocButton->setMaximumWidth(120);
    findAllDocButton = new QPushButton("Find in all Doc", this);
    findAllDocButton->setMaximumWidth(120);
    closeButton = new QPushButton("close", this);
    closeButton->setMaximumWidth(120);
    matchWholeWordOnlyBox = new QCheckBox("Match whole word only", this);
    matchCaseBox = new QCheckBox("Match case", this);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(findLabel, 0, 1, 1, 1);
    layout->addWidget(findNameEditBox, 0, 2, 1, 11);
    layout->addWidget(downFindButton, 0, 13, 1, 1);
    layout->addWidget(upFindButton, 0, 14, 1, 1);
    layout->addWidget(countButton, 1, 13, 1, 2);
    layout->addWidget(findNowDocButton, 2, 13, 1, 2);
    layout->addWidget(findAllDocButton, 3, 13, 1, 2);
    layout->addWidget(closeButton, 4, 13, 1, 2);
    layout->addWidget(matchWholeWordOnlyBox, 2, 0, 1, 2);
    layout->addWidget(matchCaseBox, 3, 0, 1, 2);

    connect(downFindButton, SIGNAL(clicked()), this, SLOT(findNameDown()));
    connect(upFindButton, SIGNAL(clicked()), this, SLOT(findNameUp()));
    connect(countButton, SIGNAL(clicked()), this, SLOT(countText()));


}

QString FindTextWidget::getFindName()
{
    return findNameEditBox->currentText();
}

void FindTextWidget::addFindName(QString addName)
{
    findNameEditBox->addItem(addName);
}

void FindTextWidget::setFindName(QString setName)
{
    findNameEditBox->setEditText(setName);
}

bool FindTextWidget::isFind(QString findText)
{
    return findNameEditBox->findText(findText) != -1;
}

void FindTextWidget::findName(bool isDown)
{
    QString findNameStr = findNameEditBox->currentText();
    if (findNameEditBox->currentText() == "")
        return;
    qint32 intCount = static_cast<MainWindow*>(parent())
            ->mainEditor->lighterFindText(findNameStr, isDown);
    qDebug() << intCount;
}

void FindTextWidget::findNameDown()
{
    findName(true);
}

void FindTextWidget::findNameUp()
{
    findName(false);
}

void FindTextWidget::countText()
{
    qDebug() << "count: ";
    QString findCountName = findNameEditBox->currentText();
    if (findCountName == "")
        return;
    qint32 count = static_cast<MainWindow*>(parent())->
            mainEditor->returnCountText(findCountName,
                                        matchWholeWordOnlyBox->isChecked(),
                                        matchCaseBox->isChecked());
    qDebug() << count;
}


//setMaxCount(5)
RenameTextWidget::RenameTextWidget(QWidget* parent)
    : QWidget(parent)
{
    findLabel = new QLabel("Find: ", this);
    findNameEditBox = new QComboBox(this);
    findNameEditBox->setEditable(true);
    reNameEditBox = new QComboBox(this);
    reNameEditBox->setEditable(true);
    upFindButton = new QPushButton("up", this);
    upFindButton->setMaximumWidth(30);
    downFindButton = new QPushButton("Find next", this);
    downFindButton->setMaximumWidth(80);
    renameButton = new QPushButton("rename", this);
    renameButton->setMaximumWidth(120);
    renameAllButton = new QPushButton("rename all", this);
    renameAllButton->setMaximumWidth(120);
    renameAllDocButton = new QPushButton("rename all doc", this);
    renameAllDocButton->setMaximumWidth(120);
    closeButton = new QPushButton("close", this);
    closeButton->setMaximumWidth(120);
    matchWholeWordOnlyBox = new QCheckBox("Match whole word only", this);
    matchCaseBox = new QCheckBox("Match case", this);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(findLabel, 0, 1, 1, 1);
    layout->addWidget(findNameEditBox, 0, 2, 1, 11);
    layout->addWidget(reNameEditBox, 1, 2, 1, 11);
    layout->addWidget(downFindButton, 0, 13, 1, 1);
    layout->addWidget(upFindButton, 0, 14, 1, 1);
    layout->addWidget(renameButton, 1, 13, 1, 2);
    layout->addWidget(renameAllButton, 2, 13, 1, 2);
    layout->addWidget(renameAllDocButton, 3, 13, 1, 2);
    layout->addWidget(closeButton, 4, 13, 1, 2);
    layout->addWidget(matchWholeWordOnlyBox, 2, 0, 1, 2);
    layout->addWidget(matchCaseBox, 3, 0, 1, 2);

}

QString RenameTextWidget::getFindName()
{
    return findNameEditBox->currentText();
}

QString RenameTextWidget::getReName()
{
    return reNameEditBox->currentText();
}

void RenameTextWidget::addFindName(QString addName)
{
    findNameEditBox->addItem(addName);
}

void RenameTextWidget::addReName(QString addName)
{
    reNameEditBox->addItem(addName);
}

void RenameTextWidget::setFindName(QString setName)
{
    findNameEditBox->setEditText(setName);
}

bool RenameTextWidget::isFind(QString findText)
{
    return findNameEditBox->findText(findText) != -1;
}

FindTextDialog::FindTextDialog(QWidget* parent)
    :QDialog(parent)
{
    resize(600, 180);
    findTextWidget = new FindTextWidget(this);
    renameTextWidget = new RenameTextWidget(this);
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(findTextWidget, "find");
    tabWidget->addTab(renameTextWidget, "rename");
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(changeTab(int)));
}

void FindTextDialog::startWork()
{
    show();
}

void FindTextDialog::changeTab(int state)
{
    qDebug() << state;
    if (state == 0) //if findWidget
    {
        qDebug() << findTextWidget->isFind(findTextWidget->getFindName()) <<
                    findTextWidget->getFindName();
        if (!findTextWidget->isFind(renameTextWidget->getFindName()) &&
                findTextWidget->getFindName() != "")
            findTextWidget->setFindName(renameTextWidget->getFindName());
    }
    else if (state == 1)
    {
        qDebug() << renameTextWidget->isFind(renameTextWidget->getFindName()) <<
                    renameTextWidget->getFindName();
        if (!renameTextWidget->isFind(findTextWidget->getFindName()) &&
                findTextWidget->getFindName() != "")
            renameTextWidget->setFindName(findTextWidget->getFindName());
    }
}
