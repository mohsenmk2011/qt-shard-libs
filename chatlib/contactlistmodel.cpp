#include "contactlistmodel.h"

ContactListModel::ContactListModel(QObject *parent) : QAbstractListModel(parent)
{

}

QHash<int, QByteArray> ContactListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[ContactRole]="model";
    return roles;
}

QVariant ContactListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    Contact *entity =m_List[i];
    if(role==ContactRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int ContactListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool ContactListModel::removeRows(int row, int count, const QModelIndex &parent)
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

void ContactListModel::add(Contact *t)
{
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< t;
    endInsertRows();
    connect(t,SIGNAL(deleteSucceed()),this,SLOT(onDeleteSucceed()));
}

Contact* ContactListModel::at(int index)
{
    return m_List.at(index);
}

Contact* ContactListModel::find(QString userId)
{
    if(userId.isNull()||userId.isEmpty()){
        return nullptr;
    }
    qInfo()<<"there are "<<rowCount()<<" of contact in the list";
    for (int i = 0; i <rowCount() ; ++i) {
        if(m_List.at(i)->userId()==userId){
            qInfo()<<"contact found";
            return m_List.at(i);
        }
    }
    qInfo()<<"contact with userid("<<userId<<") not found";
    return nullptr;
}

bool ContactListModel::onDeleteSucceed()
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
//    int id=qobject_cast<Contact*>(sender())->id();
//    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
//        if(m_List.at(i)->id()==id){
//            beginRemoveRows(QModelIndex(),i,i);
//            m_List.removeAt(i);
//            endRemoveRows();
//            break;
//        }
//    }
    return true;
}
