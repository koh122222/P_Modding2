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


MainEditor::MainEditor(QWidget *parent) : QMainWindow(parent)
{
    //connect(fileEditor, SIGNAL(tabCloseRequested(int)), this, SLOT(closeFile(qint32)));
    //connect(fileEditor, SIGNAL(currentChanged(int)), this, SLOT(changeTab(qint32)));
    nowFont = new QFont("Courier", 12);
    //@@@@@@replace
    //createFileModButton = new NewFileButton("create such a file in the mod directory", this); //todo
    //createFileModButton->setStyleSheet("background-color: rgba(57, 69, 8, 200)");
    //createFileModButton->setVisible(false);
    //connect(createFileModButton, SIGNAL(clicked()), this, SLOT(createFileMod()));



    createCopyNewFileDialog = new CreateCopyNewFileDialog(this);

    connect(createCopyNewFileDialog, SIGNAL(accepted()), this, SLOT(createIncludeFileMod()));
    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(seeOldWindow(QWidget*,QWidget*)));
    /*
    dock = new QDockWidget("111", this);
    WorkWindow* testWindow = new WorkWindow(this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dock->setWidget(testWindow);
    dock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, dock);
    testWindow->addEditor("C:/Program Files/st/steamapps/common/Europa Universalis IV/common/advisortypes/00_advisortypes.txt", FileSystem::FS_MOD_FILE, nowFont);
    nowFileEditor = testWindow->getEditor("C:/Program Files/st/steamapps/common/Europa Universalis IV/common/advisortypes/00_advisortypes.txt");
    savedWorkWindows.push_back(testWindow);

    dock = new QDockWidget("222", this);
    WorkWindow* testWindow2 = new WorkWindow(this);
    dock->setTitleBarWidget(new QWidget());
    dock->setWidget(testWindow2);
    addDockWidget(Qt::RightDockWidgetArea, dock);
    testWindow2->addEditor("C:/Program Files/st/steamapps/common/Europa Universalis IV/common/ages/00_default.txt", FileSystem::FS_MOD_FILE, nowFont);
    nowFileEditor = testWindow2->getEditor("C:/Program Files/st/steamapps/common/Europa Universalis IV/common/ages/00_default.txt");
    savedWorkWindows.push_back(testWindow2);*/
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
    qDebug() << path;
    qDebug() << "openTextFile";
    WorkWindow* nowWindow = nullptr;
    CodeEditor* nowWorkEditor = nullptr;
    QVector<CodeEditor*> allFindEditor;
    //if Dock empty
    if (savedWorkWindows.empty())
    {
        dock = new QDockWidget(this);
        nowWindow = new WorkWindow(this);
        savedWorkWindows.push_back(nowWindow);
        dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        dock->setWidget(nowWindow);
        dock->setTitleBarWidget(new QWidget());
        addDockWidget(Qt::RightDockWidgetArea, dock);
        nowWindow->addEditor(path, fileSystem, nowFont);
        nowFileEditor = nowWindow->getEditor(path);
        return;
    }
    else
    {
        if (nowFileEditor != nullptr)
        {
            if (qobject_cast<WorkWindow*>(
                        nowFileEditor->parent()->parent())->getEditor(path)
                    != nullptr)
            {
                qobject_cast<WorkWindow*>(
                                        nowFileEditor->
                            parent()->parent())->setEditor(path);
                return;
            }
        }
        else //if
        {
            //need better find now workWindow
            nowFileEditor = savedWorkWindows[0]->getCurrentEditor();
            return;

        }

        //temp, need add work with two and more files in more windows
        for (auto c : savedWorkWindows)
        {
            CodeEditor* returnEditor = c->getEditor(path);
            if (returnEditor != nullptr)
                return; //temp!!!
        }
    }
    qDebug() << "500";
    //if has window and dont has copy
    nowWindow = qobject_cast<WorkWindow*>(nowFileEditor->parent()->parent());
    nowWindow->addEditor(path, fileSystem, nowFont);
    nowFileEditor = nowWindow->getEditor(path);
    return;
}

void MainEditor::setFont(QFont* newFont)
{
    for (auto editWindow : savedWorkWindows)
    {
        editWindow->setNewFont(newFont);
    }
}

QFont* MainEditor::getFont()
{
    return nowFont;
}

void MainEditor::saveAllFile()
{

    for (auto saveWindow : savedWorkWindows)
        saveWindow->saveAllFile();

}

void MainEditor::saveFile()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
                static_cast<WorkWindow*>(nowFileEditor->parent()->parent())
                ->saveFile(qobject_cast<CodeEditor*>(nowFileEditor));
}

void MainEditor::saveFile(CodeEditor* saveEditor)
{
    //////////////////////////////////!!!!!!
    //now dont need. will be delete
    ////////////////////////////////////////
}

void MainEditor::closeAllFile()
{
    /*
    if (allOpenFile.empty())
        return;
    for (qint32 i = 0; i < allOpenFile.size(); ++i) // now i really don't like map(
    {
        auto c = allOpenFile.begin();
        for (qint32 t = 0; t < i; ++t)
            ++c;
        if(closeFile(fileEditor->indexOf(c->second)))
            --i;
    }*/
}
void MainEditor::closeFile()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
                static_cast<WorkWindow*>(nowFileEditor->parent()->parent())
                ->closeFile(qobject_cast<CodeEditor*>(nowFileEditor));
}

//void MainEditor::closeFile(CodeEditor* saveEditor)
//{
//    //NEED SAVE FILE... EHHHHH
//
//}


bool MainEditor::closeFile(CodeEditor* closeEditor)
{
    /*
    for (auto c : allOpenFile)
    {
        qDebug() << "!!!" << c.first;
    }

    CodeEditor* deleteEditor = static_cast<CodeEditor*>(fileEditor->widget(index));
    if (deleteEditor == nullptr)
        return false;
    auto needIt = find_if(allOpenFile.begin(), allOpenFile.end(),
                     [deleteEditor] (std::pair<QString, CodeEditor*> el)
        { return el.second == deleteEditor; });
    fileEditor->setCurrentWidget(deleteEditor);

    QMessageBox::StandardButton reply;
    if (deleteEditor->document()->isModified())
    {
        reply = QMessageBox::question(this, "",
                                        tr("The file was changed. Save?"),
                                        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    }
    else
        reply = QMessageBox::No;
    if (reply == QMessageBox::Yes || reply == QMessageBox::No)//if close
    {
        if (reply == QMessageBox::Yes)
        {
            saveFile(deleteEditor);
        }
        qDebug() << "delete: " << needIt->first;
        allOpenFile.erase(needIt);
        fileEditor->removeTab(index);
        delete deleteEditor; //this doesn't work completely ((

        qDebug() << "close";
        return true;
    }
    else
        return false;//else - cancel*/


}

void MainEditor::copyText()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
        static_cast<CodeEditor*>(nowFileEditor)->copy();
    //if (fileEditor->currentWidget() != nullptr)
        //static_cast<CodeEditor*>(fileEditor->currentWidget())->copy();
}
void MainEditor::cutText()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
        static_cast<CodeEditor*>(nowFileEditor)->cut();
    //if (fileEditor->currentWidget() != nullptr)
        //static_cast<CodeEditor*>(fileEditor->currentWidget())->cut();
}
void MainEditor::pasteText()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
        static_cast<CodeEditor*>(nowFileEditor)->paste();
    //if (fileEditor->currentWidget() != nullptr)
        //static_cast<CodeEditor*>(fileEditor->currentWidget())->paste();
}
void MainEditor::backText()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
        static_cast<CodeEditor*>(nowFileEditor)->undo();
    //if (fileEditor->currentWidget() != nullptr)
        //static_cast<CodeEditor*>(fileEditor->currentWidget())->undo();
}
void MainEditor::forwardText()
{
    if (qobject_cast<CodeEditor*>(nowFileEditor) != nullptr)
        static_cast<CodeEditor*>(nowFileEditor)->redo();
    //if (fileEditor->currentWidget() != nullptr)
        //static_cast<CodeEditor*>(fileEditor->currentWidget())->redo();
}

qint32 MainEditor::returnCountText(QString cText, bool matchWhileWordOnly,
                                   bool matchCase)
{
/*
    QRegularExpression findExpression;
    if (matchWhileWordOnly)
        findExpression.setPattern("\\b" + cText + "\\b");
    else
        findExpression.setPattern(cText);

    if (!matchCase)
        findExpression.setPatternOptions(
                    QRegularExpression::CaseInsensitiveOption);
    if (fileEditor->currentWidget() != nullptr)
        countFindName = static_cast<CodeEditor*>(fileEditor->currentWidget())
            ->toPlainText().count(findExpression);
    else
        countFindName = -1;
    return countFindName;*/
}

void MainEditor::updateAllHighlighter()
{
    for (auto c : savedWorkWindows)
    {
        ;//c->updateAllHighlighter();
    }
}

qint32 MainEditor::lighterFindText(QString fText, bool down)
{
    /*
    QTextCursor nowCursor = static_cast<CodeEditor*>(fileEditor->currentWidget())->textCursor();
    qint32 nowPt;
    qint32 newPt;
    if (down)
    {
        //to move to the next word
        nowCursor.movePosition(QTextCursor::EndOfWord);
        nowPt = nowCursor.position();

        newPt = static_cast<CodeEditor*>(fileEditor->currentWidget())->toPlainText().mid(nowPt).indexOf(fText);
        if (newPt != -1) //add start str if find
        {
            newPt += nowPt;
        }
        if (newPt == -1) //if dont find after ptr
        {
            newPt = static_cast<CodeEditor*>(fileEditor->currentWidget())->toPlainText().mid(0, nowPt).indexOf(fText);
        }
    }
    else
    {
        //to move to the next word
        nowCursor.movePosition(QTextCursor::StartOfWord);
        nowPt = nowCursor.position();

        newPt = static_cast<CodeEditor*>(fileEditor->currentWidget())->toPlainText().mid(0, nowPt).lastIndexOf(fText);
        if (newPt == -1) //if dont find before ptr
        {
            newPt = static_cast<CodeEditor*>(fileEditor->currentWidget())->toPlainText().mid(nowPt).lastIndexOf(fText);
            if (newPt != -1) //if find
                newPt += nowPt;
        }
    }

    if (newPt != -1) // if find
    {
        newPt += fText.size();
        QTextCursor ptr = static_cast<CodeEditor*>(fileEditor->currentWidget())->textCursor();
        ptr.setPosition(newPt);
        static_cast<CodeEditor*>(fileEditor->currentWidget())->setTextCursor(ptr);
        return static_cast<CodeEditor*>(fileEditor->currentWidget())->toPlainText().count(fText);
    }
    else
    {
        return 0;
    }


*/
    return 5;
}

void MainEditor::nowWorkWindowDeleted(WorkWindow* deletedWindow)
{
    savedWorkWindows.erase(savedWorkWindows.begin() +
                          savedWorkWindows.indexOf(deletedWindow));
    nowFileEditor = nullptr;
}

void MainEditor::resizeEvent(QResizeEvent *event)
{
    /*
    //QWidget::resizeEvent(event); //why not need? okey
    updateAllHighlighter();
    if (createFileModButton != nullptr && (fileEditor->currentIndex() == -1));
        createFileModButton->resizeGeometryEvent();*/
}

void MainEditor::changeTab(qint32 index)
{
    /*
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
    //currentEditor = static_cast<CodeEditor*>(fileEditor->widget(index));*/
}

void MainEditor::createFileMod()
{
    /*
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
    }*/

}

void MainEditor::createIncludeFileMod()
{
    /*
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


*/

}

void MainEditor::seeOldWindow(QWidget* newW)
{
    seeOldWindow(nowFileEditor, newW);
}

void MainEditor::seeOldWindow(QWidget* oldW, QWidget* newW)
{
    if (qobject_cast<CodeEditor*>(newW) != nullptr)
    {
        qDebug() << "change CodeWindow " << newW;
        nowFileEditor = newW;
    }
    //CodeEditor* NewWidget = newW;
}
