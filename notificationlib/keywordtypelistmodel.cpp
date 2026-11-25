#include "keywordtypelistmodel.h"

KeywordTypeListModel::KeywordTypeListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_List={};
}

QHash<int, QByteArray> KeywordTypeListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[KeywordTypeRole]="currentKeywordType";
    return roles;
}

QVariant KeywordTypeListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    KeywordType *entity =m_List[i];
    if(role==KeywordTypeRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int KeywordTypeListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool KeywordTypeListModel::removeRows(int row, int count, const QModelIndex &parent)
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

void KeywordTypeListModel::add(KeywordType *e)
{
    if(e->keywordTypeId()==0){
        foreach (KeywordType* i, m_List) {
            if(i->keywordTypeId()==0){
                return;//اگر یک آیتم پیش فرض وجود دارد برگرد
            }
        }
    }
    connect(e,SIGNAL(deleteSucceed()),this,SLOT(itemHasRemoved()));
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< e;
    endInsertRows();
}

void KeywordTypeListModel::edit(int id, QString value)
{
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_List.at(i)->keywordTypeId()==id) {
            m_List.at(i)->setValue(value);
            break;
        }
    }
}

Keyword* KeywordTypeListModel::find(int keywordId)
{
    for (int i = 0; i < rowCount() ; ++i) {
        auto keys=m_List.at(i)->keywords();
        for (int j = 0; j < keys->rowCount(); ++j) {
            auto key=keys->find(keywordId);
            if(key!=nullptr){
                return key;
            }
        }
    }
    return nullptr;
}
void KeywordTypeListModel::edit(KeywordType *e)
{
    edit(e->keywordTypeId(),e->value());
}

void KeywordTypeListModel::loadFromResponse(QString response)
{
    removeRows();
    QJsonDocument doc=QJsonDocument::fromJson(response.toUtf8());
    QJsonArray array=doc.array();

    for (int i = 0; i < array.count(); ++i) {
        QJsonValue val=array.at(i);
        QJsonObject obj=val.toObject();
        KeywordType* r=new KeywordType(obj.value("id").toInt(),obj.value("value").toString());
        add(r);
    }
}

void KeywordTypeListModel::itemHasRemoved()
{
    qDebug()<<"0000000000[ KeywordTypeListModel::itemHasRemoved ]0000000000";
    KeywordType* item=qobject_cast<KeywordType*>(sender());
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_List.at(i)->keywordTypeId()==item->keywordTypeId()&&m_List.at(i)->value()==item->value())
        {
            beginRemoveRows(QModelIndex(),i,i);
            qDebug()<<"----------[ KeywordTypeListModel::itemHasRemoved ]-----------";
            m_List.removeAt(i);
            endRemoveRows();
            break;
        }
    }
    qDebug()<<"99999999[ KeywordTypeListModel::itemHasRemoved ]999999999";
}
