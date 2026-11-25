#ifndef FILEUPLOADSTATUS_H
#define FILEUPLOADSTATUS_H

#include <QObject>

class FileUploadStatus : public QObject
{
    Q_OBJECT
public:
    enum class FileUploadStatusEnum:unsigned int
    {
        Unknown = 0,
        /// when file is selected with ImageEditor or FileExplorer should set status to NotStarted
        NotStarted=1,
        Started=2,
        Succeed=3,
        Faild=4,
        IsUploding=5,
    };
    Q_ENUM(FileUploadStatusEnum)
};

#endif // FILEUPLOADSTATUS_H
