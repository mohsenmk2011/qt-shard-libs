#ifndef ROLELISTMODEL_H
#define ROLELISTMODEL_H

#include <QObject>
#include<role.h>
#include<QAbstractListModel>
#include<QDebug>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonValue>
#include<QJsonObject>

class RoleListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RoleListModel(QObject *parent = nullptr);
    enum RoleRoles{
        RoleRole=Qt::UserRole+1
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void addRole(Role* r);
    void editRole(QString name,bool selected);
    void updateRole(Role *role);
    void loadFromResponse(QString response);
    void changeSelectedRole(QString roleName,bool selected);
signals:
    void scrolledToEnd() const;
private slots:
    void removeRole();
private:
    QList<Role*> m_Roles;
};

#endif // ROLELISTMODEL_H
