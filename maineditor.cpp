#include "maineditor.h"
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QFileInfo>
#include <QRegExp>
#include <QMessageBox>
#include <QDialog>
#include "mainwindow.h"
#include "gamefiles.h"
#include "newfilebutton.h"


MainEditor::MainEditor(QWidget *parent) : QWidget(parent)
{
    fileEditor = new TabEditor(this);
    fileEditor->setTabsClosable(true);
    connect(fileEditor, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(qint32)));
    connect(fileEditor, SIGNAL(currentChanged(int)), this, SLOT(changeTab(qint32)));
    nowFont = new QFont("Courier", 12);
    createFileModButton = new NewFileButton("create such a file in the mod directory", this); //todo
    createFileModButton->setStyleSheet("background-color: rgba(57, 69, 8, 200)");
    createFileModButton->setVisible(false);
    connect(createFileModButton, SIGNAL(clicked()), this, SLOT(createFileMod()));

    layout = new QVBoxLayout(this);
    layout->addWidget(fileEditor);
    layout->setContentsMargins(0,0,0,0);
    layout->setMargin(0);



    createCopyNewFileDialog = new CreateCopyNewFileDialog(this);

    connect(createCopyNewFileDialog, SIGNAL(accepted()), this, SLOT(createIncludeFileMod()));




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
        fileEditor->setCurrentWidget(newCodeEditor);


    }
}

void MainEditor::setFont(QFont* newFont)
{
    for (auto editItem : allOpenFile)
        editItem.second->setFont(*newFont);
}

void MainEditor::saveAllFile()
{
    for (auto c: allOpenFile)
        saveFile(c.second);

}

void MainEditor::saveFile()
{
    saveFile(static_cast<CodeEditor*>(fileEditor->currentWidget()));
}

void MainEditor::saveFile(CodeEditor* saveEditor)
{
    //CodeEditor* saveEditor = static_cast<CodeEditor*>(fileEditor->currentWidget());
    if (saveEditor == nullptr)
        return;
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [saveEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == saveEditor; });
    qDebug() << needIt->first;
    QString placeMod = static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceMod();
    if (needIt->first.mid(0, placeMod.size()) == placeMod)
    {
        QFile writeFile(needIt->first);
        writeFile.open(QFile::Text | QFile::WriteOnly);
        QTextStream out(&writeFile);
        out << saveEditor->toPlainText();
    }
}

void MainEditor::closeAllFile()
{
    while (!allOpenFile.empty())
    {
        auto c = allOpenFile.begin();
        qDebug() << c->first;
        closeFile(fileEditor->indexOf(c->second));
    }
}
void MainEditor::closeFile()
{
    closeFile(fileEditor->currentIndex());
}
/*
void MainEditor::closeFile(CodeEditor* saveEditor)
{
    //NEED SAVE FILE... EHHHHH

}
*/

void MainEditor::closeFile(qint32 index)
{
    for (auto c : allOpenFile)
    {
        qDebug() << "!!!" << c.first;
    }

    CodeEditor* deleteEditor = static_cast<CodeEditor*>(fileEditor->widget(index));
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [deleteEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == deleteEditor; });
    qDebug() << needIt->first;
    allOpenFile.erase(needIt);
    fileEditor->removeTab(index);
    delete deleteEditor; //this doesn't work completely ((
    qDebug() << "really?";
}

void MainEditor::resizeEvent(QResizeEvent *event)
{
    //QWidget::resizeEvent(event); //why not need? okey
    if (createFileModButton != nullptr && (fileEditor->currentIndex() == -1));
        createFileModButton->resizeGeometryEvent();
}

void MainEditor::changeTab(qint32 index)
{
    if (index == -1)
    {
        createFileModButton->setVisible(false);
        return;
    }
    CodeEditor* newNowEditor = static_cast<CodeEditor*>(fileEditor->widget(index));
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [newNowEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == newNowEditor; });
    QString dirGame = static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceGame();
    if (dirGame == needIt->first.mid(0, dirGame.size()))
    {
        createFileModButton->setVisible(true);
    }
    else
    {
        createFileModButton->setVisible(false);
    }
}

void MainEditor::createFileMod()
{
    CodeEditor* nowEditor = static_cast<CodeEditor*>(fileEditor->currentWidget());
    if (nowEditor == nullptr)
        return;
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [nowEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == nowEditor; });
    QString shortFileName = fileEditor->tabText(fileEditor->currentIndex());
    QString dirFileOfTheGame = needIt->first;
    dirFileOfTheGame = dirFileOfTheGame.mid(0, needIt->first.lastIndexOf(shortFileName));

    QStringRef relativeDirFile = dirFileOfTheGame.midRef(
                static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceGame().size());
    QString dirFileOfTheMod =
            static_cast<MainWindow*>(parent()->parent()->parent())->getPlaceMod() +
            relativeDirFile;


    qDebug() << dirFileOfTheGame;
    qDebug() << relativeDirFile;
    qDebug() << dirFileOfTheMod;
    qDebug() << shortFileName;

    if (!(QRegExp("\\d*").exactMatch(shortFileName.mid(0, 2)))) //if first two symbol don't have numbers (not include file)
    {
        qDebug() << "open not include file";
        QFileInfo gameFile(dirFileOfTheMod + shortFileName);
        qDebug() << gameFile;
        if(gameFile.exists() && gameFile.isFile()) //if the file exists
        {
            qDebug() << "f";
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "",
                                            tr("The file already exists. Want to open it?"),
                                            QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes)//if need open mod file
            {
                QString stringModFile(dirFileOfTheMod + shortFileName);
                openTextFile(stringModFile, FileSystem::MOD_FILE);
            }
            return;
        }
        else
        {
            QDir().mkpath(dirFileOfTheMod);
            QFile nowFile(dirFileOfTheMod + shortFileName);
            nowFile.open(QIODevice::WriteOnly  |  QIODevice::Text);
            QTextStream writer(&nowFile);
            writer << nowEditor->toPlainText().toUtf8();
            nowFile.close();
            QString newNowFile = dirFileOfTheMod + shortFileName;
            openTextFile(newNowFile, FileSystem::MOD_FILE);
        }
    }
    else //if first two symbol HAVE numbers (include file)
    {
        createCopyNewFileDialog->setCreateFileInfo("Creating a new file to include");
        createCopyNewFileDialog->setNowFileInfo("TODO");
        createCopyNewFileDialog->setNameFile(dirFileOfTheMod + shortFileName, true);
        createCopyNewFileDialog->clearBoxes();
        createCopyNewFileDialog->open();
    }

}

void MainEditor::createIncludeFileMod()
{
    QString fullNameFile = createCopyNewFileDialog->getFullNewName();
    qDebug() << fullNameFile << "!";
     QFileInfo gameFile(fullNameFile);
     if (gameFile.exists() && gameFile.isFile())
     {
         QMessageBox::StandardButton reply;
         reply = QMessageBox::question(this, "",
                                         tr("The file already exists. Want to open it?"),
                                         QMessageBox::Yes | QMessageBox::No);
         if (reply == QMessageBox::Yes)//if need open mod file
         {
             QString stringModFile(fullNameFile);
             openTextFile(stringModFile, FileSystem::MOD_FILE);
         }
         return;
     }
     else
     {
         qDebug() << createCopyNewFileDialog->getReplaceTrue();
         if(createCopyNewFileDialog->getReplaceTrue())//////////////////////////////////////////////////////
         {
             QDir().mkpath(fullNameFile.mid(0, fullNameFile.lastIndexOf("/")));
             QFile nowFile(fullNameFile);
             nowFile.open(QIODevice::WriteOnly  |  QIODevice::Text);
             QTextStream writer(&nowFile);
             writer << static_cast<CodeEditor*>(fileEditor->currentWidget())->toPlainText();
             nowFile.close();
             openTextFile(fullNameFile, FileSystem::MOD_FILE);

         }
         else
         {
             QDir().mkpath(fullNameFile.mid(0, fullNameFile.lastIndexOf("/")));
             QFile nowFile(fullNameFile);
             nowFile.open(QIODevice::WriteOnly  |  QIODevice::Text);
             QTextStream writer(&nowFile);
             nowFile.close();
             openTextFile(fullNameFile, FileSystem::MOD_FILE); ////////
         }
     }




}
