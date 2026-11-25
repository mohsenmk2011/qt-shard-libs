#include "notifylistmodel.h"

NotifyListModel::NotifyListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_Notifies={};
}

QHash<int, QByteArray> NotifyListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NotifyRole]="model";
    return roles;
}

QVariant NotifyListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_Notifies.size()){
        return  QVariant(QVariant::Invalid);
    }
    else if (i==m_Notifies.count()-1) {
        emit scrolledToEnd();
    }
    auto intro=m_Notifies.at(i);
    if(role==NotifyRole){
        return QVariant::fromValue(intro);
    }
    else {
        return  QVariant(QVariant::Invalid);
    }
}

int NotifyListModel::rowCount(const QModelIndex &parent) const
{
    return m_Notifies.count();
}

bool NotifyListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),0,c-1);
    for (int i = 0; i < c&&rowCount()>0; ++i) {
        m_Notifies.removeAt(0);
    }
    endRemoveRows();
    return true;
}

void NotifyListModel::addItem(Notify *n)
{
    for (int i = 0; i < m_Notifies.count(); ++i) {
        if(m_Notifies[i]->fileId()==n->fileId())
        {
            return;
        }
    }
    connect(n,SIGNAL(deleteSucceed()),this,SLOT(removeItem()));
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_Notifies<<n;
    endInsertRows();
}

void NotifyListModel::removeItem()
{
    Notify* n=qobject_cast<Notify*>(sender());
    int c=rowCount();
    qInfo()<<"rowCount=> "<<rowCount();
    if(c<=0){
        qInfo()<<"rowcount is 0 so return;";
        return;
    }
    for (int i = 0; i <rowCount() &&rowCount()>0; ++i) {
        qInfo()<<"i=> "<<i;
        if(m_Notifies.at(i)->fileId()==n->fileId()){
            qInfo()<<"at index "<<i<<"Was Found and id is "<<m_Notifies.at(i)->fileId();

            beginRemoveRows(QModelIndex(),i,i);
            m_Notifies.removeAt(i);
            endRemoveRows();
            break;
        }
        else {
            qCritical()<<"at index "<<i<<"Was not Found and id is "<<m_Notifies.at(i)->fileId();
        }
    }
}

Notify *NotifyListModel::get(int index)
{
    return m_Notifies.at(index);
}
