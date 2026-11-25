#include "fileutility.h"

FileUtility::FileUtility(QObject *parent) : QObject(parent)
{

}

void FileUtility::save(QByteArray bytes,QString fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly)){
        return;
    }
    file.write(bytes);
    file.close();
}

QByteArray FileUtility::load(QUrl fileName)
{
    QFile file(fileName.toLocalFile());
    if(file.open(QIODevice::ReadOnly)){
        return file.readAll();
    }
    return QByteArray();
}
//TODO:read as json file
