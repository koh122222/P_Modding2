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

class CustomInterfaceDialog : public QDialog
{
    Q_OBJECT
public:
    CustomInterfaceDialog(QWidget* parent);
    QLabel* ModEditorLabel;
    QLabel* fontLabel;

    QGroupBox* FontEditor;
    QLabel* familyFontLabel;
    QComboBox* fontBox;
    QLabel* sizeLabel;
    QSpinBox* sizeBox;
    QCheckBox* antiallias;

    QLabel* themeEditorLabel;
    QGroupBox* themeEditor;
    QComboBox* themeBox;

    QPushButton* okButton;
    QPushButton* cancelButton;
    QPushButton* applyButton;


};

#endif // CUSTOMINTERFACEDIALOG_H
