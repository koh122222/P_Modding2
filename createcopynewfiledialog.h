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
    QCheckBox *nameToReplaceBox;
    QString nameFile;
    QLineEdit *newNameEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;
    QGridLayout* layout;


public:
    CreateCopyNewFileDialog(QWidget *parent);
    void setCreateFileInfo(QString in_createFileInfo);
    void setNowFileInfo(QString in_nowFileInfo);
    void setNameFile(QString in_nameFile, bool upName);
    void clearBoxes();
    QString getFullNewName();
    QString getNewName();
    bool getReplaceTrue();

private slots:
    void changeNameEdit(int state);
    void changeReplaceBox(int state);
};

#endif // CREATECOPYNEWFILE_H
