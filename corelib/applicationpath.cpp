#include "applicationpath.h"

ApplicationPath::ApplicationPath(QObject *parent) : QObject(parent)
{

}

QString ApplicationPath::applicationDataPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)[0];
}

QString ApplicationPath::pictureLocationPath()
{
    return QStandardPaths::standardLocations(QStandardPaths::PicturesLocation)[0];
}

QString ApplicationPath::imagesFolderPath()
{
    return applicationDataPath()+"/Images/";
}

QString ApplicationPath::notifyimagesFolderPath()
{
    return imagesFolderPath()+"notify/";
}

QString ApplicationPath::filesFolderPath()
{
    return applicationDataPath()+"/Files/";
}

QString ApplicationPath::videoFolderPath()
{
    return applicationDataPath()+"/Videos/";
}

QString ApplicationPath::soundFolderPath()
{
    return applicationDataPath()+"/Sounds/";
}

void ApplicationPath::makeSureVideoFolderPathExsists()
{
    QDir dir(videoFolderPath());
    if(!dir.exists()){
        dir.mkpath(videoFolderPath());
    }
}

void ApplicationPath::makeSureSoundsFolderPathExsists()
{
    QDir dir(soundFolderPath());
    if(!dir.exists()){
        dir.mkpath(soundFolderPath());
    }
}
QString ApplicationPath::userFolderPath()
{
    QString path=applicationDataPath()+"/Images/User/";
    makeSurePathExsists(path);
    return path;
}

void ApplicationPath::makeSureApplicationDataPathExsists()
{
    QString appDataPath=applicationDataPath();

    QDir adptah(appDataPath);
    if(!adptah.exists())
    {
        adptah.mkpath(appDataPath);
    }
}
void ApplicationPath::makeSurePathExsists(QString path)
{
    QDir imgDir(path);
    if(!imgDir.exists()){
        imgDir.mkpath(path);
    }
}
QString ApplicationPath::currentExerciseImagesFolderPath(int exerciseId,bool checkExistance)
{

    QString path=imagesFolderPath();
    makeSurePathExsists(path);
    path +=QString::number(exerciseId)+"/";
    if(exerciseId!=0&& checkExistance){
        QDir currentimgDir(path);
        if(!currentimgDir.exists()){
            currentimgDir.mkdir(path);
        }
    }
    return path;
}
