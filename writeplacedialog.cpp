#include "writeplacedialog.h"
#include <mainwindow.h>

#include <QDir>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QCoreApplication>
WritePlaceDialog::WritePlaceDialog(QWidget* parent)
    :QDialog(parent)
{
    resize(600, 300);
    liteInfProgram = new QLabel("Paradox modding", this);
    infPlaceGame = new QLabel("Game location", this);
    infPlaceMod = new QLabel("Mod Place", this);

    nowGameBox = new QComboBox(this);
    placeGameBox = new QComboBox(this);
    placeModBox = new QComboBox(this);
    {
        qint32 i = 0;
        for (auto& c : static_cast<MainWindow*>(parent)->allGameBase)
        {
            nowGameBox->insertItem(i, c.first);
            ++i;

        }
    }

    QFile placeGame(QCoreApplication::applicationDirPath() + "//ProgramFiles//placeGame.txt", this);
    placeGame.open(QFile::ReadOnly | QFile::Text);
    QTextStream gameStream(&placeGame);
    for (qint32 i = 0; !gameStream.atEnd(); ++i)
        placeGameBox->insertItem(i, gameStream.readLine());
    placeGame.close();

    QFile placeMod(QCoreApplication::applicationDirPath() + "//ProgramFiles//placeMod.txt", this);
    placeMod.open(QFile::ReadOnly | QFile::Text);
    QTextStream modStream(&placeMod);
    for (qint32 i = 0; !modStream.atEnd(); ++i)
        placeModBox->insertItem(i, modStream.readLine());
    placeMod.close();

    placeGameButton = new QPushButton("Browse..", this);
    placeModButton = new QPushButton("Browse..", this);
    acceptButton = new QPushButton("OK", this);

    layout = new QGridLayout(this);
    layout->addWidget(liteInfProgram, 0, 0);
    layout->addWidget(nowGameBox, 1, 0, 1, 6);
    layout->addWidget(infPlaceGame, 2, 0);
    layout->addWidget(placeGameBox, 2, 1, 1, 4);
    layout->addWidget(placeGameButton, 2, 5);
    layout->addWidget(infPlaceMod, 3, 0);
    layout->addWidget(placeModBox, 3, 1, 1, 4);
    layout->addWidget(placeModButton, 3, 5);
    layout->addWidget(acceptButton, 4, 5);

    connect(placeGameButton, SIGNAL(clicked()), this, SLOT(selectGamePlace()));
    connect(placeModButton, SIGNAL(clicked()), this, SLOT(selectModPlace()));




}

void WritePlaceDialog::setLiteInfProgram(QString newInf)
{
    liteInfProgram->setText(newInf);
}
QString WritePlaceDialog::getNowPlaceGame()
{
    QString tempName = placeGameBox->currentText();
    return tempName;
}
QString WritePlaceDialog::getNowPlaceMod()
{
    QString tempName = placeModBox->currentText();
    return tempName;
}

QString WritePlaceDialog::getNowGame()
{
    QString tempName = nowGameBox->currentText();
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

