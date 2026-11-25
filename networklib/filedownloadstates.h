#ifndef FILEDOWNLOADSTATES_H
#define FILEDOWNLOADSTATES_H

#include <QObject>

class FileDownloadStates : public QObject
{
    Q_OBJECT
public:
    enum class FileDownloadStatesEnum:unsigned int
    {
        NotStarted=0,
        Faild=1,
        Succeed=2,
        Started=3,
        ErrorInSaving=4,
        FileExists=5,
        IsDownloading=6,
        FileNotFound = 7,
    };
    Q_ENUM(FileDownloadStatesEnum)
};

#endif // FILEDOWNLOADSTATES_H
