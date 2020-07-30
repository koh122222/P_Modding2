#include "createcopynewfiledialog.h"
#include <QDebug>
CreateCopyNewFileDialog::CreateCopyNewFileDialog(QWidget* parent)
    :QDialog(parent)
{
    resize(200, 150);
    createFileInfo = new QLabel("##createFileInfo", this);
    nowFileInfo = new QLabel("##nowFileInfo");
    newNameBox = new QCheckBox("Use the new full name ", this);
    newNameEdit = new QLineEdit(this);
    okButton = new QPushButton("OK",this);
    cancelButton = new QPushButton("cancel", this);

    newNameEdit->setReadOnly(true);

    layout = new QGridLayout(this);
    layout->addWidget(createFileInfo, 0, 0, 1, 2);
    layout->addWidget(newNameBox, 1, 0, 1, 2);
    layout->addWidget(newNameEdit, 2, 0, 1, 2);
    layout->addWidget(nowFileInfo, 3, 0, 1, 2);
    layout->addWidget(okButton, 4, 0);
    layout->addWidget(cancelButton, 4, 1);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(newNameBox, SIGNAL(stateChanged(int)), this, SLOT(changeNameEdit(int)));

}

void CreateCopyNewFileDialog::setCreateFileInfo(QString in_createFileInfo)
{
    createFileInfo->setText(in_createFileInfo);
}

void CreateCopyNewFileDialog::setNowFileInfo(QString in_nowFileInfo)
{
    nowFileInfo->setText(in_nowFileInfo);
}

void CreateCopyNewFileDialog::setNameFile(QString in_nameFile)
{
    nameFile = in_nameFile;
    QString shortName = in_nameFile.mid(in_nameFile.lastIndexOf("/") + 1);
    qint32 nowNumber = shortName.mid(0, 2).toInt() + 1;
    QString SNumber = QString::number(nowNumber);
    if (nowNumber < 10)
        SNumber = QString("0") + SNumber;
    newNameEdit->setText(SNumber + shortName.mid(2));


}

QString CreateCopyNewFileDialog::getFullNewName()
{
    QString temp = nameFile.mid(0, nameFile.lastIndexOf("/") + 1) + newNameEdit->text();
    return temp;
}

QString CreateCopyNewFileDialog::getNewName()
{
    return newNameEdit->text();
}

void CreateCopyNewFileDialog::changeNameEdit(int state)
{
    if (!state)
    {
        setNameFile(nameFile);
        newNameEdit->setReadOnly(true);
    }
    else
        newNameEdit->setReadOnly(false);
}

