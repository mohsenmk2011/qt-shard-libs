#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<file.h>
#include<downloadservicemanager.h>

class DownloadManager : public JooyaNetwork
{
    Q_OBJECT
public:
    explicit DownloadManager(QObject *parent = nullptr);
    ~DownloadManager();

    void setNotificationText(QString text);

    DownloadServiceManager* downloadService();

    /// will start download all files
    Q_INVOKABLE void startDownload();
    Q_INVOKABLE void add(QList<File*> fls);
    Q_INVOKABLE void add(QString link);
    Q_INVOKABLE void add(File* file);
signals:
    void totalFileDownloaded();
private slots:
    void updateRatio();
    void updateDownloadCount();
    void onDownloadStateChanged();
    void onNewServiceMessage(QString message);
    void onNewAppeMessage(QString appMessage);
private:
    void download(File* f);
    File* findFile(QString link);
    int m_CountToDownload;
    int m_CountDownloaded;
    int m_CountFailed;
    QString m_NotificationText;
    ///current file that is displaying it's ratio on notification
    int m_CurrentFileIndex;
#if defined(Q_OS_ANDROID)
    QJniObject m_App_or_Service_BroadcastReceiver;
#endif
    QList<File*> files;
    DownloadServiceManager* m_DownloadServiceManager;
};

#endif // DOWNLOADMANAGER_H
