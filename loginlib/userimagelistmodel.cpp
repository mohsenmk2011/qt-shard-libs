#include "userimagelistmodel.h"

UserImageListModel::UserImageListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_List={};
}

QHash<int, QByteArray> UserImageListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[UserImageRole]="argUserImage";
    return roles;
}

QVariant UserImageListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    UserImage *entity =m_List[i];
    if(role==UserImageRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int UserImageListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool UserImageListModel::removeRows(int row, int count, const QModelIndex &parent)
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

bool UserImageListModel::removeAt(int index)
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),index,index);
    m_List.removeAt(index);
    endRemoveRows();
    return true;
}

UserImage* UserImageListModel::get(int index)
{
    if(m_List.count()>0){
        if(index>=0&&index<m_List.count()){
            return  m_List.at(index);
        }
    }
    return nullptr;
}

void UserImageListModel::removeDefualts()
{
    for (int i = 0; i < rowCount(); ++i) {
        if(get(i)->isDefault()){
            removeAt(i);
        }
    }
}

void UserImageListModel::add(UserImage *u)
{
    connect(u,SIGNAL(deleted()),this,SLOT(deleteItem()));
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< u;
    endInsertRows();
}

void UserImageListModel::insert(UserImage *u, int index)
{
    beginInsertRows(QModelIndex(),index,index);
    m_List.insert(index,u);
    endInsertRows();
    connect(u,SIGNAL(deleted()),this,SLOT(deleteItem()));
}

bool UserImageListModel::deleteItem()
{
    int id=qobject_cast<UserImage*>(sender())->fileId();
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        if(m_List.at(i)->fileId()==id){
            beginRemoveRows(QModelIndex(),i,i);
            m_List.removeAt(i);
            endRemoveRows();
            break;
        }
    }
    emit deletedItem();
    return true;
}
