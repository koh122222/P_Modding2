#ifndef CUSTOMINTERFACEDIALOG_H
#define CUSTOMINTERFACEDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QFont>
#include <QFontDatabase>

class CustomInterfaceDialog : public QDialog
{
    Q_OBJECT
    QStringList allTheme;
public:
    CustomInterfaceDialog(QWidget* parent);
    QLabel* ModEditorLabel;
    QLabel* fontLabel;

    QGroupBox* fontEditor;
    QLabel* familyFontLabel;
    QComboBox* fontBox;
    QLabel* sizeLabel;
    QSpinBox* sizeBox;

    QLabel* themeEditorLabel;
    QGroupBox* themeEditor;
    QComboBox* themeBox;

    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* applyButton;


    QFontDatabase fontDataBase;

    void showStart();

public slots:
    void startChange();


};

#endif // CUSTOMINTERFACEDIALOG_H
