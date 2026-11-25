#ifndef CONTACTMANAGER_H
#define CONTACTMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<contact.h>
#include<contactlistmodel.h>
#include<chat.h>
#include<listmanager.h>


class ContactManager : public  ListManager {
    Q_OBJECT
    Q_PROPERTY(ContactListModel* listModel READ listModel CONSTANT)
    Q_PROPERTY(Contact* me READ me CONSTANT)
public:
    explicit ContactManager(QObject *parent = nullptr);
    ~ContactManager();

    Q_INVOKABLE void getList();

    ContactListModel* listModel();
    Contact* me();
    void loadFromFile();
    Q_INVOKABLE void saveInFile();
    QJsonArray toJsonArray();
signals:
private slots:
    void onGetListFinished();
    void onNewInfoReceived(WebSocketInfo *info);
private:
    ContactListModel m_ListModel;
    Contact* m_Me;
};

#endif // CONTACTMANAGER_H
