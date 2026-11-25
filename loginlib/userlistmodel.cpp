#include "userlistmodel.h"

UserListModel::UserListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_users={};
}

QHash<int, QByteArray> UserListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[UserRole]="argUser";
    return roles;
}

QVariant UserListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_users.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_users.count()-1){
        emit scrolledToEnd();
    }

    User *entity =m_users[i];
    if(role==UserRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int UserListModel::rowCount(const QModelIndex &parent) const
{
    return m_users.count();
}

bool UserListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),0,c-1);
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        m_users.removeAt(0);
    }
    endRemoveRows();
    return true;
}

void UserListModel::addUser(User *u)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_users<< u;
    endInsertRows();
}
