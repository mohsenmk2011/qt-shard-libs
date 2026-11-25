#ifndef FILE_H
#define FILE_H

#include <QObject>
#include<jooyanetwork.h>
#include<QFile>
#include<QJsonObject>
#include<QDir>
#include<qdebug.h>
#include<applicationpath.h>
#include<filedownloadstates.h>
#include<fileuploadstatus.h>
#include<QUrl>
#include<QNetworkRequest>

class File : public JooyaNetwork
{
    Q_OBJECT

    Q_PROPERTY(QString downloadLink READ downloadLink WRITE setDownloadLink NOTIFY downloadLinkChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QString imageName READ imageName WRITE setImageName NOTIFY imageNameChanged)
    Q_PROPERTY(int fileId READ fileId WRITE setFileId NOTIFY fileIdChanged)

    Q_PROPERTY(qint64 bytesSent READ bytesSent WRITE setBytesSent NOTIFY bytesSentChanged)
    Q_PROPERTY(qint64 bytesTotal READ bytesTotal WRITE setBytesTotal NOTIFY bytesTotalChanged)

    Q_PROPERTY(float upDownRatio READ upDownRatio WRITE setUpDownRatio NOTIFY upDownRatioChanged)
    Q_PROPERTY(QString folderPath READ folderPath WRITE setFolderPath NOTIFY folderPathChanged)
    Q_PROPERTY(QString ext READ ext WRITE setExt NOTIFY extChanged)
    Q_PROPERTY(FileDownloadStates::FileDownloadStatesEnum downloadState READ downloadState WRITE setDownloadState NOTIFY downloadStateChanged)
    Q_PROPERTY(FileUploadStatus::FileUploadStatusEnum uploadStatus READ uploadStatus WRITE setUploadStatus NOTIFY uploadStatusChanged)
    Q_PROPERTY(bool isDownloaded READ isDownloaded WRITE setIsDownloaded NOTIFY isDownloadedChanged)
    Q_PROPERTY(bool isExists READ isExists WRITE setIsExists NOTIFY isExistsChanged)
    Q_PROPERTY(bool isExistsInServer READ isExistsInServer WRITE setIsExistsInServer NOTIFY isExistsInServerChanged)

public:
    explicit File(QObject *parent = nullptr);
    File(QString link);
    File(QString link,QString path);
    File(QString link,QString path, QString extension);

    QString downloadLink();
    void setDownloadLink(QString url);

    QUrl url();
    void setUrl(QUrl p);

    QString imageName();
    void setImageName(QString n);

    int fileId();
    void setFileId(int id);

    qint64 bytesSent();
    void setBytesSent(qint64 t);

    qint64 bytesTotal();
    void setBytesTotal(qint64 t);

    float upDownRatio();
    void setUpDownRatio(float ratio);

    QString folderPath();
    void setFolderPath(QString folderPath);

    QString ext();
    void setExt(QString ext);

    FileDownloadStates::FileDownloadStatesEnum downloadState();
    void setDownloadState(FileDownloadStates::FileDownloadStatesEnum ds);

    bool isDownloaded();
    void setIsDownloaded(bool isD);

    bool isExists();
    void setIsExists(bool isD);

    Q_INVOKABLE bool exists();

    Q_INVOKABLE virtual void download(bool useApiUrl=false, bool isFullUrl=false);
    Q_INVOKABLE virtual QNetworkReply* upload(QString url, QJsonObject obj);
    Q_INVOKABLE virtual void upload();
    Q_INVOKABLE bool remove();
    bool isVideo(QString ext="");
    bool isAudio(QString ext="");
    bool save(QByteArray textContent);
    bool saveJson(QJsonArray array);
    QByteArray read();

    QUrl getUrl(QString name);
    const FileUploadStatus::FileUploadStatusEnum &uploadStatus() const;
    void setUploadStatus(const FileUploadStatus::FileUploadStatusEnum &newUploadStatus);

    bool isExistsInServer() const;
    void setIsExistsInServer(bool newIsExistsInServer);

signals:
 void downloadLinkChanged();
 void urlChanged();
 void imageNameChanged();
 void fileIdChanged();
 void upDownRatioChanged();
 void folderPathChanged();
 void extChanged();
 void bytesSentChanged();
 void bytesTotalChanged();
 void downloadStateChanged();
 void isDownloadedChanged();
 void isExistsChanged();
 void uploadStatusChanged();
 void isExistsInServerChanged();
 void deleteSucceed();

 private slots:
 void updownLoadingProgress(qint64 bytesSent, qint64 bytesTotal);
 void onUploadProgress(qint64 bytesSent, qint64 bytesTotal);
 void onDownloadFinishd();
 void refreshPath();
 void onUpload();

private:
    QString m_DowloadLink;
    QUrl m_Url;
    QString m_Name;
    int m_FileId;
    qint64 m_BytesSent;
    qint64 m_BytesTotal;
    float m_UpDownRatio;
    QString m_FolderPath;
    QString m_Extension;
    FileDownloadStates::FileDownloadStatesEnum m_DownloadState;
    bool m_IsDownloaded;
    bool m_IsExists;
    void makeSureFolderExsists();
    void initializeFolderPath(QString ext);
    FileUploadStatus::FileUploadStatusEnum m_uploadStatus;
    bool m_isExistsInServer;
};

#endif // FILE_H
