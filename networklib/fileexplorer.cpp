#include "fileexplorer.h"

FileExplorer::FileExplorer(QObject *parent)
    : QObject{parent}
{
    setFolderPath(m_ApplicationPath.imagesFolderPath()+"BookCropped/");
    m_ApplicationPath.makeSurePathExsists(folderPath());
}

const QString &FileExplorer::folderPath() const
{
    return m_folderPath;
}

void FileExplorer::setFolderPath(const QString &newFolderPath)
{
    if (m_folderPath == newFolderPath)
        return;
    m_folderPath = newFolderPath;
    m_ApplicationPath.makeSurePathExsists(newFolderPath);
    emit folderPathChanged();
}

void FileExplorer::getList()
{
    QDir currentFolder = QDir(folderPath());
    QStringList entries = currentFolder.entryList(QStringList()<<"*.jpg");

    qDebug()<<"entries.size() => "<<entries.size();
    ImageFile* newImg = nullptr;
    for (int i=0; i<entries.size(); i++)
    {
        entries[i].prepend(currentFolder.absolutePath() + "/");
        newImg = new ImageFile();
        newImg->setUrl(QUrl(entries[i]));
        m_ListModel.addImage(newImg);
        qDebug()<<"==> "<<entries[i];
        qDebug()<<"m_ListModel.rowCount() => "<<m_ListModel.rowCount();
    }
}

ImageListModel *FileExplorer::listModel()
{
    return &m_ListModel;
}
