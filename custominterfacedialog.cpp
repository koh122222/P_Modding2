#include "custominterfacedialog.h"

CustomInterfaceDialog::CustomInterfaceDialog(QWidget* parent)
    :QDialog(parent)
{
    ModEditorLabel = new QLabel("Mod Editor", this);
    fontLabel = new QLabel("Font", this);

    FontEditor = new QGroupBox(this);
    familyFontLabel = new QLabel("Family: ", FontEditor);
    fontBox = new QComboBox(FontEditor);
    sizeLabel = new QLabel("Size: ", FontEditor);
    sizeBox = new QSpinBox(FontEditor);
    antiallias = new QCheckBox("antiallias", FontEditor);
    QGridLayout *fontLayout = new QGridLayout(FontEditor);
    fontLayout->addWidget(familyFontLabel, 0, 0, 1, 1);
    fontLayout->addWidget(fontBox, 0, 1, 1, 2);
    fontLayout->addWidget(sizeLabel, 0, 3, 1, 1);
    fontLayout->addWidget(sizeBox, 0, 4, 1, 1);
    fontLayout->addWidget(antiallias, 0, 5, 1, 1);

    themeEditorLabel = new QLabel("Theme Editor", this);
    themeEditor = new QGroupBox(this);
    themeBox = new QComboBox(themeEditor);
    QGridLayout* themeLayout = new QGridLayout(themeEditor);
    themeLayout->addWidget(themeBox, 0, 0);

    okButton = new QPushButton("OK", this);
    cancelButton = new QPushButton("Cancel", this);
    applyButton = new QPushButton("Apply", this);
    QGridLayout* mainLayout = new QGridLayout(this);
    mainLayout->addWidget(ModEditorLabel, 0, 0, 1, 1);
    mainLayout->addWidget(fontLabel, 1, 0, 1, 1);
    mainLayout->addWidget(FontEditor, 2, 0, 2, 6);
    mainLayout->addWidget(themeEditorLabel, 4, 0, 1, 1);
    mainLayout->addWidget(themeEditor, 5, 0, 1, 6);
    mainLayout->addWidget(okButton, 6, 3, 1, 1);
    mainLayout->addWidget(cancelButton, 6, 4, 1, 1);
    mainLayout->addWidget(applyButton, 6, 5, 1, 1);



}