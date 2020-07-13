#include "writeplacedialog.h"
#include <QDir>
#include <QFileDialog>

WritePlaceDialog::WritePlaceDialog(QWidget* parent)
    :QDialog(parent)
{
    resize(600, 300);
    liteInfProgram = new QLabel("Paradox modding", this);
    infPlaceGame = new QLabel("Game location", this);
    infPlaceMod = new QLabel("Mod Place", this);

    placeGameBox = new QComboBox(this);
    placeModBox = new QComboBox(this);

    placeGameButton = new QPushButton("Browse..", this);
    placeModButton = new QPushButton("Browse..", this);
    acceptButton = new QPushButton("OK", this);

    layout = new QGridLayout(this);
    layout->addWidget(liteInfProgram, 0, 0);
    layout->addWidget(infPlaceGame, 1, 0);
    layout->addWidget(placeGameBox, 1, 1, 1, 4);
    layout->addWidget(placeGameButton, 1, 5);
    layout->addWidget(infPlaceMod, 2, 0);
    layout->addWidget(placeModBox, 2, 1, 1, 4);
    layout->addWidget(placeModButton, 2, 5);
    layout->addWidget(acceptButton, 3, 5);

    connect(placeGameButton, SIGNAL(clicked()), this, SLOT(selectGamePlace()));
    connect(placeModButton, SIGNAL(clicked()), this, SLOT(selectModPlace()));



}

void WritePlaceDialog::setLiteInfProgram(QString newInf)
{
    liteInfProgram->setText(newInf);
}
QString WritePlaceDialog::getNowPlaceGame()
{
    QString tempName = placeGameBox->itemText(0);;
    return tempName;
}
QString WritePlaceDialog::getNowPlaceMod()
{
    QString tempName = placeModBox->itemText(0);;
    return tempName;
}



void WritePlaceDialog::selectGamePlace()
{
    QString inDir =
        QDir::toNativeSeparators(
                QFileDialog::getExistingDirectory(
                    this, tr("Find Files"), QDir::currentPath()));

    if (!inDir.isEmpty()) {
        if (placeGameBox->findText(inDir) == -1)
            placeGameBox->addItem(inDir);
        placeGameBox->setCurrentIndex(placeGameBox->findText(inDir));
    }
}

void WritePlaceDialog::selectModPlace()
{
    QString inDir =
        QDir::toNativeSeparators(
                QFileDialog::getExistingDirectory(
                    this, tr("Find Files"), QDir::currentPath()));

    if (!inDir.isEmpty()) {
        if (placeModBox->findText(inDir) == -1)
            placeModBox->addItem(inDir);
        placeModBox->setCurrentIndex(placeModBox->findText(inDir));
    }
}

