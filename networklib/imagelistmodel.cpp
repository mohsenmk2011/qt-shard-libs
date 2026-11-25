#include "imagelistmodel.h"

ImageListModel::ImageListModel(QObject *parent)
    : QAbstractListModel{parent}
{
    m_List = {};
}

QHash<int, QByteArray> ImageListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[UserRole]="model";
    return roles;
}

QVariant ImageListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    ImageFile *entity =m_List[i];
    if(role==UserRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int ImageListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool ImageListModel::existes(QUrl imageUrl)
{
    int c=rowCount();
    for (int i = 0; i <c&&rowCount()>0; ++i) {
        if(m_List.at(i)->url()==imageUrl){
            return true;
        }
    }
    return false;
}

bool ImageListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),0,c-1);
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        m_List.removeAt(0);
    }
    endRemoveRows();
    return true;
}

void ImageListModel::addImage(ImageFile *u)
{
    if(u==nullptr){
        return;
    }
    if(existes(u->url())){
        return;
    }
    connect(u,&ImageFile::deleteSucceed,this,&ImageListModel::imageDeleted);
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< u;
    endInsertRows();
}

ImageFile *ImageListModel::getNewImage()
{
    return getImage(0);
}

ImageFile *ImageListModel::getImage(int fileId)
{
    for (int i = 0; i < rowCount(); ++i) {
        if(m_List.at(i)->fileId()==fileId){
            return m_List.at(i);
        }
    }
    return nullptr;
}

QList<ImageFile *> ImageListModel::getList()
{
    return m_List;
}

void ImageListModel::imageDeleted()
{
    qDebug()<<"image was deleted from disk-> remove it from list model";
    ImageFile *b=qobject_cast<ImageFile*>(sender());
    int c=rowCount();
    for (int i = 0; i <c&&rowCount()>0; ++i) {
        if(m_List.at(i)->fileId()==b->fileId()){
            beginRemoveRows(QModelIndex(),i,i);
            m_List.removeAt(i);
            endRemoveRows();
            return;
        }
    }
}
