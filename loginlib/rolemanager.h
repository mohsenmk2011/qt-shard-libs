#ifndef ROLEMANAGER_H
#define ROLEMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<rolelistmodel.h>
#include<QJsonArray>
#include<QJsonDocument>

class RoleManager : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(RoleListModel* listModel READ listModel CONSTANT)
public:
    explicit RoleManager(QObject *parent = nullptr);
    Q_INVOKABLE void getList();
    RoleListModel* listModel();
    Q_INVOKABLE void add();

signals:
public slots:
    void getListFinished();
private:
    RoleListModel m_ListModel;
};

#endif // ROLEMANAGER_H
