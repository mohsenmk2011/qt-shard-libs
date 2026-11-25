#include "chatlistmodel.h"

ChatListModel::ChatListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_List={};
}

QHash<int, QByteArray> ChatListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[ChatRole]="model";
    return roles;
}

QVariant ChatListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    Chat *entity =m_List[i];
    if(role==ChatRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int ChatListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool ChatListModel::removeRows(int row, int count, const QModelIndex &parent)
{
//    int c=0;
//    if(count==0){//of count ==0 so all rows should be removed
//        c=rowCount()-1;
//    }
//    if(c<0){
//        return  true;
//    }
//    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
//        beginRemoveRows(QModelIndex(),row,row+c);
//        m_List.removeAt(row);
//        endRemoveRows();
//        qInfo()<<"count=>> "<<m_List.count();
//    }
//    return true;

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

void ChatListModel::append(Chat *e)
{
    if(e==nullptr){
        return;
    }
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< e;
    endInsertRows();
    connect(e,&Chat::deleteSucceed,this,&ChatListModel::onDeleteSucceed);
}

Chat *ChatListModel::at(int index)
{
    return m_List.at(index);
}

Chat *ChatListModel::find(QString chatId)
{
    if(chatId.isNull()||chatId.isEmpty()){
        qWarning()<<"contactId is null";
        return nullptr;
    }
    for (int i = 0; i <rowCount()&&rowCount()>0 ; ++i) {
        qDebug()<<"chatId(in conversation contactid=> "<<m_List.at(i)->chatId();
        if(m_List.at(i)->chatId()==chatId){
            return m_List.at(i);
        }
    }
    qWarning()<<"chat not found in "<<rowCount()<<" chats";
    return nullptr;
}

void ChatListModel::onDeleteSucceed()
{
    int c=rowCount();
    if(c<=0){
        return;
    }
    Chat* currentChat=qobject_cast<Chat*>(sender());
    int index = m_List.indexOf(currentChat);
    if(index== -1)
    {
        return;
    }
    beginRemoveRows(QModelIndex(),index,index);
    m_List.removeAt(index);
    endRemoveRows();
}
