#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<QImage>
#include<imageutility.h>
#include<userlistmodel.h>
#include<QJsonArray>
#include<user.h>
#include<listmanager.h>

class UserManager : public ListManager
{
    Q_OBJECT
    Q_PROPERTY(UserListModel* listModel READ listModel CONSTANT)    
public:
    explicit UserManager(QObject *parent = nullptr);

    Q_INVOKABLE void getList();
    UserListModel* listModel();
signals:
private slots:
    void getListFinishded();
private:
    UserListModel m_ListModel;
};

#endif // USERMANAGER_H
