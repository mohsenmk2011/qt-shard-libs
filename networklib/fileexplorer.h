#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QObject>
#include<applicationpath.h>
#include<imagelistmodel.h>
#include<imagefile.h>

class FileExplorer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString folderPath READ folderPath WRITE setFolderPath NOTIFY folderPathChanged)
    Q_PROPERTY(ImageListModel* listModel READ listModel CONSTANT)
public:
    explicit FileExplorer(QObject *parent = nullptr);

    const QString &folderPath() const;
    void setFolderPath(const QString &newFolderPath);

    Q_INVOKABLE void getList();

    ImageListModel *listModel();

signals:
    void folderPathChanged();

private:
    ApplicationPath m_ApplicationPath;
    QString m_folderPath;
    ImageListModel m_ListModel;
};

#endif // FILEEXPLORER_H
