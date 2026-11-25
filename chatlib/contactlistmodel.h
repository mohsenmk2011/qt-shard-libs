#ifndef CONTACTLISTMODEL_H
#define CONTACTLISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<contact.h>
#include<qdebug.h>

class ContactListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ContactListModel(QObject *parent = nullptr);
    enum ContactRoles{
        ContactRole=Qt::UserRole+1,
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void add(Contact* t);
    Contact *find(QString userId);

    Contact *at(int index);
signals:
    void scrolledToEnd() const;

private slots:
    bool onDeleteSucceed();

private:
    QList<Contact*> m_List;


signals:

};

#endif // CONTACTLISTMODEL_H
