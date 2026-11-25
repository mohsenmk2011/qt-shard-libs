#include "filewatcher.h"

FileWatcher::FileWatcher(QObject *parent):AppPagesManager(parent)
{
    mWatcher=new QFileSystemWatcher(this);
    connect(mWatcher, &QFileSystemWatcher::directoryChanged, this, &FileWatcher::onDirectoryChanged);
    connect(mWatcher, &QFileSystemWatcher::fileChanged, this, &FileWatcher::onFileChanged);

    mTimer =new QTimer(parent);
    mTimer->setInterval(45);
    mTimer->setSingleShot(true);
    // connect timer to callback function
    connect(mTimer, &QTimer::timeout, this,&FileWatcher::onTimerTimeout);
}

void FileWatcher::onTimerTimeout(){
    qDebug()<<"is emmitting reloadQmlFile signal";
    qDebug()<<"file changed=> "<<m_ChangedFileBaseName;
    emit fileChanged(m_ChangedFileBaseName);


//    QObject* item= find(m_ChangedFileBaseName);
//    qDebug()<<"url finded item=> "<<item->property("url").toString();
//    qDebug()<<"founded item=> "<<item;
//    if(item)
//    {
////        QQuickView* view=(QQuickView*)item;
////        QObject* obj = getComponent(m_ChangedFilePath,view->parent());
////        qCritical()<<"created obj => "<<obj;
////        obj=view;

//        //view->deleteLater();
////        if(m_FileName.startsWith("com"))
////        {
////            qDebug()<<"the founded qml is component";
////            QString itemUrl=view->property("url").toString();
////            QString nullString="";

////            view->setProperty("source",QVariant::fromValue(nullString));
////            engine()->clearComponentCache();

////            qDebug()<<"source(should be null) => "<<item->property("url").toString();
////            item->setProperty("url",QVariant::fromValue(itemUrl));
////            qDebug()<<"source(should not be null) => "<<item->property("url").toString();
////        }
////        else if(m_FileName.startsWith("loader"))
////        {
////            qDebug()<<"the founded qml is loader";
////            QString itemSource=item->property("source").toString();
////            QString nullString="";

////            item->setProperty("source",QVariant::fromValue(nullString));
////            engine()->clearComponentCache();

////            qDebug()<<"source(should be null) => "<<item->property("source").toString();
////            item->setProperty("source",QVariant::fromValue(itemSource));
////            qDebug()<<"source(should not be null) => "<<item->property("source").toString();
////        }
//    }
//    else{
//        qWarning()<<"item "<<m_ChangedFileBaseName<<" not found";
//    }
    ////===================================================================
    //    bool falseValue=false;
    //    item->setProperty("active",QVariant::fromValue(falseValue));
    //    bool active=item->property("active").toBool();
    //    qDebug()<<"active (should be false) =>"<<active;

    //    item->setProperty("source",QVariant::fromValue(nullString));
    //    engine()->clearComponentCache();

    //    qDebug()<<"source(should be null) => "<<item->property("source").toString();
    //    item->setProperty("source",QVariant::fromValue(itemSource));
    //    qDebug()<<"source(should not be null) => "<<item->property("source").toString();

    //    falseValue=true;
    //    item->setProperty("active",QVariant::fromValue(falseValue));
    //    active=item->property("active").toBool();
    //    qDebug()<<"active (should be true) =>"<<active;

}

void FileWatcher::writepathcounts()
{
    qDebug()<<"files => "<<mWatcher->files().count();
    for (int i = 0; i < mWatcher->files().count(); ++i) {
        qDebug()<<"file "<<i<<mWatcher->files().at(i);
    }
    for (int i = 0; i < mWatcher->directories().count(); ++i) {
        qDebug()<<"dir "<<i<<mWatcher->directories().at(i);
    }
    qDebug()<<"directories => "<<mWatcher->directories().count();
}

void FileWatcher::addPaths(QDir directory)
{
    qCritical()<<"$$$$$$$$$$$$$$$$$$$$[ addPaths "<<directory.absolutePath()<<" ]$$$$$$$$$$$$$$$$$$$$$$$$$$";
    //    QString dirPath=directory.absolutePath();
    //    if(!(dirPath.isNull()||dirPath.isEmpty())){
    //        if(!mWatcher->directories().contains(dirPath)){
    //            mWatcher->addPaths(QStringList()<< directory.absolutePath());
    //        }
    //    }
    QStringList entries = directory.entryList(QStringList()<<"*.qml");
    for (int i=0; i<entries.size(); i++)
    {
        entries[i].prepend(directory.absolutePath() + "/");
    }
    if(entries.count()>0){
        qDebug()<<entries;
        mWatcher->addPaths(entries);
    }
    QStringList directories = directory.entryList(QStringList()<<"*",QDir::Dirs|QDir::NoSymLinks|QDir::NoDotAndDotDot);
    for (int i=0; i<directories.size(); i++)
    {
        if(!m_ExcludeDirs.contains(directories[i])){
            directories[i].prepend(directory.absolutePath() + "/");
            QDir ndir=QDir(directories[i]);
            addPaths(ndir);
        }
    }

    qCritical()<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$";
}

void FileWatcher::addExcludeDirs(QStringList dirs)
{
    m_ExcludeDirs=dirs;
    qDebug()<<"Exclude Dirs =>"<<m_ExcludeDirs;
}

void FileWatcher::setDirectory(const QString &path)
{
    QDir projectDir=QDir(path);
    if(!projectDir.exists()){
        qWarning()<<" Directory "<<path<<"doesn't exists .QML LIVE will not wrok.shadow build should be enabled";
        return;
    }
    qInfo()<<"dir sets to => "<<path;
    m_ProjectDir=projectDir;
    addPaths(m_ProjectDir);
}

void FileWatcher::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path);
    qDebug()<<"on Directory Changed => "<<path;
    mWatcher->removePaths(mWatcher->files());
    addPaths(m_ProjectDir);
}

void FileWatcher::onFileChanged(const QString &path)
{
    qDebug()<<"path changed => "<<path;
    QFileInfo file(path);
    while (!file.exists()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(180));
    }
    clearCache();
    m_ChangedFileBaseName=file.baseName();
    m_ChangedFilePath=path;

    mWatcher->addPath(path);
    //timer will emit the filechaged signal of this class
    mTimer->start();
}
