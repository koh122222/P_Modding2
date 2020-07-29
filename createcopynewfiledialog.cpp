#include "createcopynewfiledialog.h"

CreateCopyNewFileDialog::CreateCopyNewFileDialog(QWidget* parent)
    :QDialog(parent)
{
    createFileInfo = new QLabel("##createFileInfo", this);
    nowFileInfo = new QLabel("##nowFileInfo");
    newNameBox = new QCheckBox("Use the new full name ", this);
    newNameEdit = new QLineEdit(this);

    layout = new QGridLayout(this);
    layout->addWidget(createFileInfo, 0, 0);
    layout->addWidget(newNameBox, 1, 0);
    layout->addWidget(newNameEdit, 2, 0);
    layout->addWidget(nowFileInfo, 3, 0);

}

void CreateCopyNewFileDialog::setCreateFileInfo(QString& in_createFileInfo)
{
    createFileInfo->setText(in_createFileInfo);
}
void CreateCopyNewFileDialog::setNowFileInfo(QString& in_nowFileInfo)
{
    nowFileInfo->setText(in_nowFileInfo);
}
void CreateCopyNewFileDialog::setNameFile(QString& in_nameFile)
{
    nameFile = in_nameFile;
    qint32 nowNumber = in_nameFile.mid(0, 2).toInt();
    newNameEdit->setText(QString::number(nowNumber) + nameFile.mid(2));


}
QString CreateCopyNewFileDialog::getNewName()
{
    return newNameEdit->text();
}
