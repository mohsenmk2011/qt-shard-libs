#ifndef APPLICATIONPATH_H
#define APPLICATIONPATH_H

#include <QObject>
#include<QDebug>
#include<QDir>
#include<QStandardPaths>

class ApplicationPath : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationPath(QObject *parent = nullptr);

    QString applicationDataPath();
    Q_INVOKABLE QString pictureLocationPath();

    void makeSureApplicationDataPathExsists();
    QString imagesFolderPath();
    QString notifyimagesFolderPath();
    QString filesFolderPath();
    void makeSurePathExsists(QString path);
    QString currentExerciseImagesFolderPath(int bookId, bool checkExistance=false);

    ///پوشه حاوی عکس های کاربر
    QString userFolderPath();
    QString videoFolderPath();
    QString soundFolderPath();
    void makeSureVideoFolderPathExsists();
    void makeSureSoundsFolderPathExsists();
signals:

public slots:
};

#endif // APPLICATIONPATH_H
