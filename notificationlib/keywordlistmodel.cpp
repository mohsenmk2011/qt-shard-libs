#include "keywordlistmodel.h"

KeywordListModel::KeywordListModel(QObject *parent) : QAbstractListModel(parent)
{    
    m_List={};
}

QHash<int, QByteArray> KeywordListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[KeywordRole]="currentKeyword";
    return roles;
}

QVariant KeywordListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    Keyword *entity =m_List[i];
    if(role==KeywordRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int KeywordListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool KeywordListModel::removeRows(int row, int count, const QModelIndex &parent)
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

void KeywordListModel::add(Keyword *e)
{
    qDebug()<<"999999999999999999[ KeywordListModel::add ]999999999999";
    ///اگر یک آیتم پیش فرض وجود دارد برگرد
    if(e->keywordId()==0){
        foreach (Keyword* i, m_List) {
            if(i->keywordId()==0){
                return;
            }
        }
    }
    connect(e,SIGNAL(deleteSucceed()),this,SLOT(itemHasRemoved()));
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< e;
    endInsertRows();
    qDebug()<<"m_List.count()=>"+QString::number(m_List.count());
    qDebug()<<"00000000000000000000[ KeywordListModel::add ]00000000000000";
}

void KeywordListModel::edit(int id, QString value)
{
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_List.at(i)->keywordId()==id) {
            m_List.at(i)->setValue(value);
            break;
        }
    }
}

void KeywordListModel::edit(Keyword *e)
{
    edit(e->keywordId(),e->value());
}

void KeywordListModel::loadFromResponse(QString response)
{
    removeRows();
    QJsonDocument doc=QJsonDocument::fromJson(response.toUtf8());
    QJsonArray array=doc.array();
    for (int i = 0; i < array.count(); ++i) {
        add(new Keyword(array.at(i).toObject()));
    }
}

Keyword* KeywordListModel::find(int keywordId)
{
    for (int i = 0; i < rowCount() ; ++i) {
        if (m_List.at(i)->keywordId()==keywordId) {
            return m_List.at(i);
        }
    }
    return nullptr;
}

void KeywordListModel::itemHasRemoved()
{
    qDebug()<<"0000000000[ KeywordListModel::itemHasRemoved ]0000000000";
    Keyword* item=qobject_cast<Keyword*>(sender());
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_List.at(i)->keywordId()==item->keywordId()&&m_List.at(i)->value()==item->value())
        {
            beginRemoveRows(QModelIndex(),i,i);
            qDebug()<<"----------[ KeywordListModel::itemHasRemoved ]-----------";
            m_List.removeAt(i);
            endRemoveRows();
            break;
        }
    }
    qDebug()<<"99999999[ KeywordListModel::itemHasRemoved ]999999999";
}
