#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QObject>
#include <functional>
#include <QFileSystemWatcher>
#include <QDir>
#include <QTimer>
#include <QDebug>
#include <QString>
#include<QDirIterator>
#include<QUrl>
#include<QCoreApplication>
#include<QtQml>
#include<thread>
#include<apppagesmanager.h>

using namespace std;

class FileWatcher : public AppPagesManager
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit FileWatcher(QObject *parent = nullptr);

//    void addCallback(std::function<void()> callback);

    void addExcludeDirs(QStringList dirs);

    void writepathcounts();
    void setDirectory(const QString &path);
signals:
    void fileChanged(QString fileName);
private slots:
    void onDirectoryChanged(const QString &path);
    void onFileChanged(const QString &path);
    void onTimerTimeout();
private:
    void addPaths(QDir directory);
    QFileSystemWatcher*    mWatcher;
    QDir                  m_ProjectDir;
    QTimer*                mTimer;
    QString m_ChangedFileBaseName;
    QString m_ChangedFilePath;
    QStringList m_ExcludeDirs;

};

#endif // FILEWATCHER_H
