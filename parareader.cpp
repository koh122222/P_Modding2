#include "parareader.h"
#include "mainwindow.h"
#include <QDebug>
paraReader::paraReader(QObject * parent)
    : QObject(parent)
{
    gamepath = qobject_cast<MainWindow *>(parent)->getPlaceGame();
    qDebug()<< "1";
    AllPar::modVector[TYPE_MOD::M_EU_EVENTS] = model_maker(modReader());
    qDebug()<< "2";
}

QVector <QString> paraReader::modReader()
{
    QVector <QString> mods;

    QString compath = gamepath +"//common";
    QDir comdir(compath);
   // qDebug()<< compath;
    QFileInfoList dirslist = comdir.entryInfoList(QDir::Dirs);
    //QStringList filter ;
    //filter << "*.txt";
    //comdir.setNameFilters(filter);
    //qDebug()<< comdir.path();
    QFileInfoList fileslist = comdir.entryInfoList(QStringList()<< "*.txt");

    for (auto dirinfo:dirslist)
    {

        QDir dir(dirinfo.filePath());
        //qDebug()<< dir.path();
        QFileInfoList fileslist_2 = dir.entryInfoList(QStringList()<< "*.txt");

        for (int i = 0; i <  fileslist_2.size(); ++i) {
            QFileInfo fileInfo =  fileslist_2.at(i);
            QFile modfile(fileInfo.filePath());
            modfile.open(QFile::Text | QFile::ReadOnly);
            QTextStream filestream(&modfile);
            QString opened_file = filestream.readAll();

            //qDebug()<< fileInfo.fileName();
            qint32 wordsize = 0;
            for (int i=0; i <opened_file.size()-4;i++ )
            {
                if ((opened_file[i]==' ')
                        ||(opened_file[i]=='\n')
                        ||(opened_file[i]=='#')
                        ||(opened_file[i]=='\t')
                        ||(opened_file[i]=='\\')
                        ||(opened_file[i]=='\"')
                        ||(opened_file[i]=='1')
                        ||(opened_file[i]=='2')
                        ||(opened_file[i]=='3')
                        ||(opened_file[i]=='4')
                        ||(opened_file[i]=='5')
                        ||(opened_file[i]=='6')
                        ||(opened_file[i]=='7')
                        ||(opened_file[i]=='8')
                        ||(opened_file[i]=='9')
                        ||(opened_file[i]=='0'))
                    wordsize =0;
                else
                    wordsize++;


                if ((opened_file[i+2]== '=')&&(opened_file[i+4]!= '{'))
                    {
                        QString mod = opened_file.mid(i+1-wordsize, wordsize);
                        bool uniq = true;
                        for (auto a:mods)
                            if (a==mod){
                                uniq = false;
                                break;
                            }
                        if(uniq)
                            mods.push_back(mod);
                    }
            }
        }
    }

    for (int i = 0; i <  fileslist.size(); ++i) {
        QFileInfo fileInfo =  fileslist.at(i);
        QFile modfile(fileInfo.filePath());
        modfile.open(QFile::Text | QFile::ReadOnly);
        QTextStream filestream(&modfile);
        QString opened_file = filestream.readAll();

        //qDebug()<< fileInfo.fileName();
        qint32 wordsize = 0;
        for (int i=0; i <opened_file.size()-4;i++ )
        {
            if ((opened_file[i]==' ')
                    ||(opened_file[i]=='\n')
                    ||(opened_file[i]=='#')
                    ||(opened_file[i]=='\t')
                    ||(opened_file[i]=='\\')
                    ||(opened_file[i]=='\"')
                    ||(opened_file[i]=='1')
                    ||(opened_file[i]=='2')
                    ||(opened_file[i]=='3')
                    ||(opened_file[i]=='4')
                    ||(opened_file[i]=='5')
                    ||(opened_file[i]=='6')
                    ||(opened_file[i]=='7')
                    ||(opened_file[i]=='8')
                    ||(opened_file[i]=='9')
                    ||(opened_file[i]=='0'))
                wordsize =0;
            else
                wordsize++;


            if ((opened_file[i+2]== '=')&&(opened_file[i+4]!= '{'))
                {
                    QString mod = opened_file.mid(i+1-wordsize, wordsize);
                    bool uniq = true;
                    for (auto a:mods)
                        if (a==mod){
                            uniq = false;
                            break;
                        }
                    if(uniq)
                        mods.push_back(mod);
                }
        }
    }
    //for (auto a:mods)
    //    qDebug()<< a;


    return  mods;
}

ModModel paraReader::model_maker(QVector <QString> codenames)
{
    qDebug()<< "AA";
    ModModel model;
    QString locpath = gamepath +"\\localisation";
    QDir comdir(locpath);

    QFileInfoList fileslist = comdir.entryInfoList(QStringList()<< "*english*");
    for (int i = 0; i <  fileslist.size(); ++i)
    {
        QFileInfo fileInfo =  fileslist.at(i);
        QFile modfile(fileInfo.filePath());
        modfile.open(QFile::Text | QFile::ReadOnly);
        QTextStream filestream(&modfile);
        QString opened_file = filestream.readAll();

        qint32 wordsize = 0;
        QString right="";
        QString left="";
        bool finded= false;
        for (int i=0; i <opened_file.size();i++ )
        {
            if ((opened_file[i]== '\n')&&(finded))
                {
                    right = opened_file.mid(i+1-wordsize, wordsize-1);
                    ModPair pair (left, right);
                    qDebug()<< "AОА";
                    model.insert(pair);
                    qDebug()<< "AООООA";
                    finded= false;
                }
            if ((opened_file[i]==' ')
                    ||(opened_file[i]=='\n'))
                wordsize =0;
            else
                wordsize++;
            if (opened_file[i]== ':')
                {

                    left = opened_file.mid(i+1-wordsize, wordsize+1);
                    for (auto code:codenames)
                        if (left == code){
                            qDebug()<< "ЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫ";
                            finded = true;
                        }
                }
        }
    }
    for (auto code:codenames)
    {
        bool finded = false;
        for (auto pair:model)
            if (pair.first == code){
                qDebug()<< "ЫЫЫЫХЫ";
                finded = true;
            }
        if (!finded)
        {
            ModPair paiR (code, "");
            model.insert(paiR);
        }
    }
    qDebug()<< "ООООООООО";
    return model;
}
