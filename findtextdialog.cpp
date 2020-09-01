#include "findtextdialog.h"

/*
    QLabel* findLabel;
    QComboBox* findNameEditBox;
    QPushButton* upFindButton;
    QPushButton* downFindButton;
    QPushButton* countButton;
    QPushButton* findNowDocButton;
    QPushButton* findAllDocButton;
    QPushButton* closeButton;
    QCheckBox* findFullNameBox;
    QCheckBox* fildWithReg;
    */

MainFinder::MainFinder(QWidget* parent)
    :QWidget(parent)
{

}

FindTextWidget::FindTextWidget(QWidget* parent)
    :MainFinder(parent)
{
    findLabel = new QLabel("Find: ", this);
    findNameEditBox = new QComboBox(this);
    findNameEditBox->setEditable(true);
    upFindButton = new QPushButton("up", this);
    upFindButton->setMaximumWidth(50);
    downFindButton = new QPushButton("down", this);
    downFindButton->setMaximumWidth(50);
    countButton = new QPushButton("count", this);
    countButton->setMaximumWidth(120);
    findNowDocButton = new QPushButton("find in this Doc", this);
    findNowDocButton->setMaximumWidth(120);
    findAllDocButton = new QPushButton("Find in all Doc", this);
    findAllDocButton->setMaximumWidth(120);
    closeButton = new QPushButton("close", this);
    closeButton->setMaximumWidth(120);
    findFullNameBox = new QCheckBox("find full name", this);
    findWithReg = new QCheckBox("find with reg", this);

    QGridLayout* layout = new QGridLayout(this);
    layout->addWidget(findLabel, 0, 1, 1, 1);
    layout->addWidget(findNameEditBox, 0, 2, 1, 11);
    layout->addWidget(upFindButton, 0, 13, 1, 1);
    layout->addWidget(downFindButton, 0, 14, 1, 1);
    layout->addWidget(countButton, 1, 13, 1, 2);
    layout->addWidget(findNowDocButton, 2, 13, 1, 2);
    layout->addWidget(findAllDocButton, 3, 13, 1, 2);
    layout->addWidget(closeButton, 4, 13, 1, 2);
    layout->addWidget(findFullNameBox, 2, 0, 1, 2);
    layout->addWidget(findWithReg, 3, 0, 1, 2);




}



FindTextDialog::FindTextDialog(QWidget* parent)
    :QDialog(parent)
{
    resize(600, 180);
    findTextWidget = new FindTextWidget(this);
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(findTextWidget, "find");

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

}
