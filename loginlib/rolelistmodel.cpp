#include "rolelistmodel.h"

RoleListModel::RoleListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_Roles={};
}

QHash<int, QByteArray> RoleListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[RoleRole]="model";
    return roles;
}

QVariant RoleListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_Roles.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_Roles.count()-1){
        emit scrolledToEnd();
    }

    Role *entity =m_Roles[i];
    if(role==RoleRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int RoleListModel::rowCount(const QModelIndex &parent) const
{
    return m_Roles.count();
}

bool RoleListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),0,c-1);
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        m_Roles.removeAt(0);
    }
    endRemoveRows();
    return true;
}

void RoleListModel::addRole(Role *r)
{
    connect(r,SIGNAL(deleted()),this,SLOT(removeRole()));
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_Roles<< r;
    endInsertRows();
}

void RoleListModel::editRole(QString name, bool selected)
{
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_Roles.at(i)->name()==name) {
            m_Roles.at(i)->setSelected(selected);
            qDebug()<<"Selected Of Role Changed=>"<<m_Roles.at(i)->name()<<"to=>"<<m_Roles.at(i)->selected();
            break;
        }
    }
}
void RoleListModel::removeRole()
{
    qDebug()<<"RoleListModel::removeRole";
    Role* rol=qobject_cast<Role*>(sender());
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_Roles.at(i)->id()==rol->id()&&m_Roles.at(i)->name()==rol->name()) {
            qDebug()<<"selected Index="<<i;
            beginRemoveRows(QModelIndex(),i,i);
            m_Roles.removeAt(i);
            endRemoveRows();
            break;
        }
    }
}
void RoleListModel::updateRole(Role* role)
{
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_Roles.at(i)->id()==role->id()) {
            qDebug()<<"selected Index="<<i;
            m_Roles.at(i)->setName(role->name());
        }
    }
}

void RoleListModel::loadFromResponse(QString response)
{
    removeRows();
    QJsonDocument doc=QJsonDocument::fromJson(response.toUtf8());
    QJsonArray array=doc.array();

    for (int i = 0; i < array.count(); ++i) {
        QJsonValue val=array.at(i);
        QJsonObject obj=val.toObject();
        Role* r=new Role(obj.value("name").toString(),obj.value("id").toString(),obj.value("selected").toBool());

        addRole(r);
    }
}

void RoleListModel::changeSelectedRole(QString roleName, bool selected)
{
    int c=rowCount();
    for (int i = 0; i < c && c>0; ++i) {
        if (m_Roles.at(i)->name()==roleName) {
            m_Roles.at(i)->setSelected(selected);
        }
    }
}
