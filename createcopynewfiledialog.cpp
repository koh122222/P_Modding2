#include "createcopynewfiledialog.h"
#include <QDebug>
CreateCopyNewFileDialog::CreateCopyNewFileDialog(QWidget* parent)
    :QDialog(parent)
{
    resize(200, 150);
    createFileInfo = new QLabel("##createFileInfo", this);
    nowFileInfo = new QLabel("##nowFileInfo");
    newNameBox = new QCheckBox("Use the new full name ", this);
    nameToReplaceBox = new QCheckBox("nameToReplace", this);
    newNameEdit = new QLineEdit(this);
    okButton = new QPushButton("OK",this);
    cancelButton = new QPushButton("cancel", this);

    newNameEdit->setReadOnly(true);

    layout = new QGridLayout(this);
    layout->addWidget(createFileInfo, 0, 0, 1, 2);
    layout->addWidget(newNameBox, 1, 0, 1, 2);
    layout->addWidget(nameToReplaceBox, 2, 0, 1, 2);
    layout->addWidget(newNameEdit, 3, 0, 1, 2);
    layout->addWidget(nowFileInfo, 4, 0, 1, 2);
    layout->addWidget(okButton, 5, 0);
    layout->addWidget(cancelButton, 5, 1);

    connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(newNameBox, SIGNAL(stateChanged(int)), this, SLOT(changeNameEdit(int)));
    connect(nameToReplaceBox, SIGNAL(stateChanged(int)), this, SLOT(changeReplaceBox(int)));

}

void CreateCopyNewFileDialog::setCreateFileInfo(QString in_createFileInfo)
{
    createFileInfo->setText(in_createFileInfo);
}

void CreateCopyNewFileDialog::setNowFileInfo(QString in_nowFileInfo)
{
    nowFileInfo->setText(in_nowFileInfo);
}

void CreateCopyNewFileDialog::setNameFile(QString in_nameFile, bool upName)
{
    nameFile = in_nameFile;
    QString shortName = in_nameFile.mid(in_nameFile.lastIndexOf("/") + 1);
    qint32 nowNumber = shortName.mid(0, 2).toInt();
    if (upName)
        ++nowNumber;
    QString SNumber = QString::number(nowNumber);
    if (nowNumber < 10)
        SNumber = QString("0") + SNumber;
    newNameEdit->setText(SNumber + shortName.mid(2));


}

void CreateCopyNewFileDialog::clearBoxes()
{
    newNameBox->setChecked(false);
    nameToReplaceBox->setChecked(false);
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
    if (state && nameToReplaceBox->isChecked())
    {
        nameToReplaceBox->setChecked(false);
        newNameEdit->setReadOnly(false);
    }
    else if (!state && nameToReplaceBox->isChecked())
    {
        setNameFile(nameFile, false);
        newNameEdit->setReadOnly(true);
    }
    else if (!state && !nameToReplaceBox->isChecked())
    {
        setNameFile(nameFile, true);
        newNameEdit->setReadOnly(true);
    }
    else if (state && !nameToReplaceBox->isChecked())
    {
        newNameEdit->setReadOnly(false);
    }
}

void CreateCopyNewFileDialog::changeReplaceBox(int state)
{
    qDebug() << state;
    if (state && newNameBox->isChecked())
    {
        newNameBox->setChecked(false);
        setNameFile(nameFile, false);
        newNameEdit->setReadOnly(true);
    }
    else if (state && !newNameBox->isChecked())
    {
        setNameFile(nameFile, false);
        newNameEdit->setReadOnly(true);
    }
    else if (!state && !newNameBox->isChecked())
    {
        setNameFile(nameFile, true);
        newNameEdit->setReadOnly(true);
    }
    else if (!state && newNameBox->isChecked())
    {
        newNameEdit->setReadOnly(false);
    }
}

