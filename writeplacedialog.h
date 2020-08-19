#ifndef WRITEPLACE_H
#define WRITEPLACE_H
#include <QDialog>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>

class WritePlaceDialog : public QDialog
{
    Q_OBJECT
    //QString moddingGame; ///?????? need?
    QGridLayout *layout;

    QLabel *liteInfProgram;
    QLabel *infPlaceGame;
    QLabel *infPlaceMod;

    QComboBox *nowGameBox;
    QComboBox *placeGameBox;
    QComboBox *placeModBox;

    QPushButton *placeGameButton;
    QPushButton *placeModButton;
    QPushButton *acceptButton;

public:
    WritePlaceDialog(QWidget *parent);
    void setLiteInfProgram(QString newInf);
    QString getNowPlaceGame();
    QString getNowPlaceMod();
    QString getNowGame();




public slots:
    void selectGamePlace();
    void selectModPlace();
};

#endif // WRITEPLACE_H
