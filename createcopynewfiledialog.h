#ifndef CREATECOPYNEWFILE_H
#define CREATECOPYNEWFILE_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
#include <QLineEdit>
class CreateCopyNewFileDialog : public QDialog
{
    Q_OBJECT
    QLabel *createFileInfo;
    QLabel *nowFileInfo;
    QCheckBox *newNameBox;
    QString nameFile;
    QLineEdit *newNameEdit;
    QGridLayout* layout;


public:
    CreateCopyNewFileDialog(QWidget *parent);
    void setCreateFileInfo(QString& in_createFileInfo);
    void setNowFileInfo(QString& in_nowFileInfo);
    void setNameFile(QString& in_nameFile);
    QString getNewName();
};

#endif // CREATECOPYNEWFILE_H
