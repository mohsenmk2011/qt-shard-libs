#ifndef USERLISTMODEL_H
#define USERLISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<user.h>

class UserListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit UserListModel(QObject *parent = nullptr);
    enum UserRoles{
        UserRole=Qt::UserRole+1
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void addUser(User* u);
signals:
    void scrolledToEnd() const;
public slots:
private:
    QList<User*> m_users;
};

#endif // USERLISTMODEL_H
