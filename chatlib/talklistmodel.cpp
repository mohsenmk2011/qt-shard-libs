#include "talklistmodel.h"

TalkListModel::TalkListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_List={};
}

QHash<int, QByteArray> TalkListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[TalkRole]="model";
    return roles;
}

QVariant TalkListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    Post *entity =m_List[i];
    if(role==TalkRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int TalkListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool TalkListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int c=0;
    if(count==0){
        c=rowCount()-1;
    }
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),row,row+c);
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        m_List.removeAt(row);
    }
    endRemoveRows();
    return true;
}

int TalkListModel::unReadTalksCount()
{
    int count=0;
    for (int i = 0; i <rowCount() ; ++i) {
        if(!m_List.at(i)->fromMe()&&!m_List.at(i)->isJustDate()){
            if(m_List.at(i)->status()!=TalkStatus::TalkStatusEnum::Seen&&m_List.at(i)->status()!=TalkStatus::TalkStatusEnum::Deleted){
                count++;
            }
        }
    }
    return count;
}

void TalkListModel::add(Post *t)
{
    auto c =rowCount();
    if(c>0){
        m_List.at(c-1)->setIsLastItem(false);
    }
    t->setIsLastItem(true);
    updateDateRows(t);
    c =rowCount();
    beginInsertRows(QModelIndex(),c,c);
    m_List<< t;
    endInsertRows();
    connect(t,SIGNAL(deleteSucceed()),this,SLOT(onDeleteSucceed()));
}

Post *TalkListModel::get(int index)
{
    return m_List.at(index);
}

Post *TalkListModel::find(QString id)
{
    int c=rowCount();
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        if(m_List.at(i)->id()==id){
            return m_List.at(i);
        }
    }
    return nullptr;
}
void TalkListModel::removeById(QString id)
{
    for (int i = 0; i <rowCount()&&rowCount()>0 ; ++i) {
        if(m_List.at(i)->id()==id){
            beginRemoveRows(QModelIndex(),i,i);
            m_List.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}


bool TalkListModel::onDeleteSucceed()
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    QString id=qobject_cast<Post*>(sender())->id();
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        if(m_List.at(i)->id()==id){
            beginRemoveRows(QModelIndex(),i,i);
            m_List.removeAt(i);
            endRemoveRows();
            break;
        }
    }
    return true;
}

void TalkListModel::updateDateRows(Post* newTalk)
{
    auto c =rowCount();
    qDebug()<<"c=> "<<c;
    if(c==0){
        beginInsertRows(QModelIndex(),c,c);
        m_List<< new Post(newTalk->date(),true);
        endInsertRows();
    }
    else
    {
        QDateTime lastDate= m_List.at(rowCount()-1)->date();
        int days=lastDate.daysTo(newTalk->date());
        if(days>0){
            beginInsertRows(QModelIndex(),c,c);
            m_List<< new Post(newTalk->date(),true);
            endInsertRows();
        }
    }
}
