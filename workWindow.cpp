#include "workwindow.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>

WorkWindow::WorkWindow(QWidget* parent)
    :QWidget(parent)
{
    openEdit = new QComboBox(this);
    delButton = new QToolButton(this);
    subTypesFile = new QComboBox(this);
    stackedWidget = new QStackedWidget(this);

//    workFiles.push_back({"full file 0",new CodeEditor(this)});
//    stackedWidget->addWidget(workFiles[0].second);
//    workFiles[0].second->setPlainText("000");
//    openEdit->addItem("page 0");
//    workFiles.push_back({"fullFile 1", new CodeEditor(this)});
//    stackedWidget->addWidget(workFiles[1].second);
//    workFiles[1].second->setPlainText("111");
//    openEdit->addItem("page 1");
//    workFiles.push_back({"fullFile 2", new CodeEditor(this)});
//    stackedWidget->addWidget(workFiles[2].second);
//    workFiles[2].second->setPlainText("222");
//    openEdit->addItem("page 2");

//    stackedWidget->removeWidget(workFiles[2].second);
//    workFiles[2].second->deleteLater();
//    openEdit->removeItem(2);
//    workFiles.push_back({"FullFile3", new CodeEditor(this)});
//    stackedWidget->addWidget(workFiles[3].second);
//    workFiles[3].second->setPlainText("333");
//    openEdit->addItem("page 3");



    QGridLayout* layout = new QGridLayout(this);

    connect(openEdit, QOverload<int>::of(&QComboBox::currentIndexChanged),
                stackedWidget, &QStackedWidget::setCurrentIndex);

    layout->addWidget(openEdit, 0, 0, 1, 5);
    layout->addWidget(delButton, 0, 5, 1, 1);
    layout->addWidget(subTypesFile, 0, 6, 1, 5);
    layout->addWidget(stackedWidget, 1, 0, 5, 11);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
}

bool WorkWindow::addEditor(QString openFile, FileSystem fileSystem, QFont* font)
{
    /*
    workFiles.push_back({"full file 0",new CodeEditor(this)});
    stackedWidget->addWidget(workFiles[0].second);
    workFiles[0].second->setPlainText("000");
    openEdit->addItem("page 0");*/
    CodeEditor* nowEditor;
    workFiles.push_back({openFile , nowEditor = new CodeEditor(this)});
    stackedWidget->addWidget(nowEditor);
    openEdit->addItem(openFile.mid(openFile.lastIndexOf("/") + 1));


    QFile file(openFile);

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return false;
    }
    QTextStream in(&file);
    QString text = in.readAll();
    nowEditor->setPlainText(text);
    file.close();
    nowEditor->setFont(*font);
    QFontMetrics metrics(*font);
    nowEditor->setTabStopDistance(metrics.horizontalAdvance("    "));
    //allOpenFile.insert(AllOpenFile::value_type(path, nowEditor));

    if (fileSystem == FileSystem::FS_GAME_FILE)
    {
        QIcon gameIcon("://resources//gameIcon//eu4_icon.jpg");
//        fileEditor->addTab(nowEditor, gameIcon,
//                           path.mid(path.lastIndexOf("/") + 1));
    }
    else if (fileSystem == FileSystem::FS_MOD_FILE)
    {
        QIcon modIcon("://resources//gameIcon//eu4_modIcon.png");
//        fileEditor->addTab(nowEditor, modIcon,
//                           path.mid(path.lastIndexOf("/") + 1));
    }


    return true;
}

bool WorkWindow::setEditor(QString fullFile)
{
    //?may be problems with index
    qint32 index;
    while (index < workFiles.size())
    {
        if (workFiles[index].first == fullFile)
        {
            openEdit->setCurrentIndex(index);
            openEdit->currentIndexChanged(index);
            return true;
        }
        ++index;
    }


    return false;
}

CodeEditor* WorkWindow::getEditor(QString findFullName)
{
    for (auto c : workFiles)
    {
        if (c.first == findFullName)
            return c.second;
    }
    return nullptr;
}

CodeEditor* WorkWindow::getCurrentEditor()
{
    return qobject_cast<CodeEditor*>(stackedWidget->currentWidget());
}
