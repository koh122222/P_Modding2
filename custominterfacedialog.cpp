#include "custominterfacedialog.h"
#include <allpar.h>
#include <QDebug>
#include <QApplication>
#include "mainwindow.h"

CustomInterfaceDialog::CustomInterfaceDialog(QWidget* parent)
    :QDialog(parent)
{
    ModEditorLabel = new QLabel("Mod Editor", this);
    fontLabel = new QLabel("Font", this);

    fontEditor = new QGroupBox(this);
    familyFontLabel = new QLabel("Family: ", fontEditor);
    fontBox = new QComboBox(fontEditor);
    sizeLabel = new QLabel("Size: ", fontEditor);
    sizeBox = new QSpinBox(fontEditor);
    QGridLayout *fontLayout = new QGridLayout(fontEditor);
    fontLayout->addWidget(familyFontLabel, 0, 0, 1, 1);
    fontLayout->addWidget(fontBox, 0, 1, 1, 2);
    fontLayout->addWidget(sizeLabel, 0, 3, 1, 1);
    fontLayout->addWidget(sizeBox, 0, 4, 1, 1);

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
    mainLayout->addWidget(fontEditor, 2, 0, 2, 6);
    mainLayout->addWidget(themeEditorLabel, 4, 0, 1, 1);
    mainLayout->addWidget(themeEditor, 5, 0, 1, 6);
    mainLayout->addWidget(okButton, 6, 3, 1, 1);
    mainLayout->addWidget(cancelButton, 6, 4, 1, 1);
    mainLayout->addWidget(applyButton, 6, 5, 1, 1);

    connect(okButton, &QPushButton::pressed, this, &CustomInterfaceDialog::accept);
    connect(cancelButton, &QPushButton::pressed, this, &CustomInterfaceDialog::accept);
    connect(applyButton, &QPushButton::pressed, this, &CustomInterfaceDialog::startChange);

    QFont tempFont = ModEditorLabel->font();
    tempFont.setWeight(QFont::Bold);
    ModEditorLabel->setFont(tempFont);
    fontBox->insertItems(0, fontDataBase.families());
    fontBox->setEditable(true);
    fontBox->setInsertPolicy(QComboBox::NoInsert);

    allTheme.push_back("Light Theme");
    allTheme.push_back("Dark Theme");
    themeBox->insertItems(0, allTheme);
    themeBox->setEditable(true);
    themeBox->setInsertPolicy(QComboBox::NoInsert);


}

void CustomInterfaceDialog::showStart()
{
    QFont* nowFont = AllPar::mObject->mainEditor->getFont();
    qint32 indexOfFamily = fontBox->findText(nowFont->family());
    if (indexOfFamily != -1)
        fontBox->setCurrentIndex(indexOfFamily);
    sizeBox->setValue(nowFont->pointSize());

    this->show();
}

void CustomInterfaceDialog::startChange()
{
    //FONT
    //fontDataBase.font(fontB)
    QFont newFont = fontDataBase.font(fontBox->currentText(), "Light", sizeBox->value());
    /////////////////////////////////////////////////////////////
    static_cast<MainWindow*>(parent())->mainEditor->setFont(&newFont);


    //THEME
    if (AllPar::interface_colors.find(themeBox->currentText()) ==
            AllPar::interface_colors.end())
        return;

    auto iColors = AllPar::interface_colors[themeBox->currentText()];

    qApp->setStyleSheet(
            "QWidget"
            "{"
            "   background-color: " + iColors["mainBGColor"] + ";"
            "   color: " + iColors["mainTextColor"] + ";"
            "}"
            "QLineEdit"
            "{"
            "   background-color: " + iColors["mainBGColor"] + ";"
            "   border-radius: 1px;"
            "   border-style: outset;"
            "   border-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ""
            "}"
            "QPlainTextEdit"
            "{"
            "   background-color: " + iColors["mainBGColor"] + ";"
            "   border-style: solid;"
            "   border-width: 0px;"
            "   border-left-width: 1px;"
            "   border-right-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "}"
            "QToolBar"
            "{"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "   border-bottom-width: 1px;"
            "   border-top-width: 1px;"
            "   border-style: solid;"
            "   border-color: " + iColors["lightBorderColor2"] + ";"
            "}"
            "QToolButton"
            "{"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "}"
            "QToolButton:hover"
            "{"
            "   background-color: " + iColors["selectBGColor"] + ";"
            "}"
            "QTabWidget:pane"
            "{"
            "   margin: 0px 0px 0px 0px"
            "}"
            "QTabBar::tab"
            "{"
            "   margin: 0px 0px 0px 0px;"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "   height: 1.2em;"
            "   border-left-width: 1px;"
            "   border-right-width: 1px;"
            "   padding-bottom: -1px;"
            "}"
            "QHeaderView::section"
            "{"
            "   margin: 0px 0px 0px 0px;"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "   border-style: solid;"
            "   border-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "   border-right-width: 0px;"
            "   border-left-width: 0px;"
            "   height: 1.2em;"
            "}"
            "QScrollBar:vertical "
            "{"
            "   border-style: solid;"
            "   border-width: 1px;"
            "   border-right-width: 0px;"
            "   border-color:" + iColors["lightBorderColor"] + ";"
            "   background-color:" + iColors["secondBGColor"] + ";"
            "   width: 14px;"
            "   margin: 13px 0px 13px 0px;"
            "}"
            "QScrollBar::handle:vertical {"
            "   background-color: " + iColors["scrollHandle"] + ";"
            "   border-style: solid;"
            "   border-width: 1px;"
            "   border-color: " + iColors["lightBorderColor3"] + ";"
            "   min-height: 20px;"
            "}"
            "QScrollBar::add-line:vertical {"
            "   border-left-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "   border-style: solid;"

            //"   margin: 1px 1px 1px 1px;"
            "   height: 13px;"
            "   subcontrol-position: bottom;"
            "   subcontrol-origin: margin;"
            "   background-image: url(:/resources/interfaceImage/arrow_bottom.png);"
            "}"

            "QScrollBar::sub-line:vertical {"
            "   border-left-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "   border-style: solid;"
            "   height: 13px;"
            "   subcontrol-position: top;"
            "   subcontrol-origin: margin;"
            "   background-image: url(:/resources/interfaceImage/arrow_top.png);"
            "}"
            "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
            "    background: none;"
            "}"
            "QTreeView"
            "{"
            "   border-style: solid;"
            "   border-width: 0px;"
            "   border-right-width: 1px;"
            "   border-color: " + iColors["lightBorderColor"] + ";"
            "}"
            "QMenuBar"
            "{"
            "   background-color: " + iColors["secondBGColor"] + ";"
            "}"
            "QMenuBar:item:selected"
            "{"
            "   background-color: " + iColors["selectBGColor"] + ";"
            "}"
            "QMenu"
            "{"
            "   margin: 0px 0px 0px 0px;"
            "   border-style: solid;"
            "   border-top-width: 1px;"
            "   border-color: " + iColors["lightBorderColor2"] + ";"
            "}"
            "QMenu::item"
            "{"
            "   height: 1.6em"

            "}"
            "QMenu::item:selected"
            "{"
            "   background-color: " + iColors["selectBGColor2"] + ";"
            "}"
            "QComboBox"
            "{"
            //"   border: 2px solid "
            "   height: 1.3em;"
            "}"
            "QComboBox QAbstractItemView::item"
            "{"
            "   background-color" + iColors["mainBGColor"] + ";"
            "}"

        );





}
