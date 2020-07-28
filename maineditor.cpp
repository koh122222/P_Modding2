#include "maineditor.h"
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <mainwindow.h>
#include "gamefiles.h"
#include "newfilebutton.h"

MainEditor::MainEditor(QWidget *parent) : QWidget(parent)
{
    fileEditor = new TabEditor(this);
    fileEditor->setTabsClosable(true);
    connect(fileEditor, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(qint32)));
    nowFont = new QFont("Courier", 12);
    createFileModButton = new NewFileButton("lol", this);
    createFileModButton->setGeometry(400, 400, 100, 100);
    createFileModButton->setStyleSheet("background-color: rgba(0, 0, 0, 90)"); //TODO
    connect(createFileModButton, SIGNAL(clicked()), this, SLOT(createFileMod()));

    layout = new QVBoxLayout(this);
    layout->addWidget(fileEditor);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);




    /*
    fileEditor = new CodeEditor(this);
    QFont fontEditor("Courier", 16);
    fileEditor->setFont(fontEditor);
    QFontMetrics metrics(fontEditor);
    fileEditor->setTabStopDistance(metrics.horizontalAdvance("    "));
*/


}

void MainEditor::openTextFile(QString &path, FileSystem fileSystem)
{
    auto c = allOpenFile.find(path);
    if (c != allOpenFile.end()) //if the tab exists
    {
        fileEditor->setCurrentWidget(c->second);
    }
    else //create new Tab
    {
        CodeEditor* newCodeEditor = new CodeEditor;
        QFile file(path);

        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll();
        newCodeEditor->setPlainText(text);
        file.close();
        newCodeEditor->setFont(*nowFont);
        QFontMetrics metrics(*nowFont);
        newCodeEditor->setTabStopDistance(metrics.horizontalAdvance("    "));
        allOpenFile.insert(AllOpenFile::value_type(path, newCodeEditor));

        if (fileSystem == MainEditor::GAME_FILE)
        {
            QIcon gameIcon("://resources//gameIcon//eu4_icon.jpg");
            fileEditor->addTab(newCodeEditor, gameIcon,
                               path.mid(path.lastIndexOf("/") + 1));
        }
        else if (fileSystem == MainEditor::MOD_FILE)
        {
            QIcon modIcon("://resources//gameIcon//eu4_modIcon.png");
            fileEditor->addTab(newCodeEditor, modIcon,
                               path.mid(path.lastIndexOf("/") + 1));
        }


    }
}

void MainEditor::setFont(QFont* newFont)
{
    for (auto editItem : allOpenFile)
        editItem.second->setFont(*newFont);
}

void MainEditor::resizeEvent(QResizeEvent *event)
{
    //QWidget::resizeEvent(event); //why not need? okey
    if (createFileModButton != nullptr)
        createFileModButton->resizeGeometryEvent();
}

void MainEditor::closeFile(qint32 index)
{
    CodeEditor* deleteEditor = static_cast<CodeEditor*>(fileEditor->widget(index));
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [deleteEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == deleteEditor; });
    allOpenFile.erase(needIt);
    fileEditor->removeTab(index);
    delete deleteEditor; //this doesn't work completely ((
}

void MainEditor::createFileMod()
{
    //1.0
    CodeEditor* nowEditor = static_cast<CodeEditor*>(fileEditor->currentWidget());
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [nowEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == nowEditor; });
    QString dirFileOfTheGame = needIt->first;
    QStringRef relativeDirFile = dirFileOfTheGame.midRef(
                static_cast<MainWindow*>(parent()->parent())->getPlaceGame().size());
    QString dirFileOfTheMod =
            static_cast<MainWindow*>(parent()->parent())->getPlaceMod() + relativeDirFile;

    QString shortFileName = fileEditor->tabText(fileEditor->currentIndex());
    qDebug() << dirFileOfTheGame;
    qDebug() << relativeDirFile;
    qDebug() << dirFileOfTheMod;
    qDebug() << shortFileName;

    if (shortFileName.midRef(0, 3) == "00_") //2.x
    {

        qDebug() << "sp00";
    }

    QFileInfo gameFile(dirFileOfTheGame);

    if(gameFile.exists() && gameFile.isFile())
        qDebug() << true;
}
