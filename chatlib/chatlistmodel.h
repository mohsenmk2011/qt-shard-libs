#ifndef CHATLISTMODEL_H
#define CHATLISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<chat.h>

class ChatListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ChatListModel(QObject *parent = nullptr);
    enum ChatRoles{
        ChatRole=Qt::UserRole+1,
    };


    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void append(Chat* e);
    Chat *at(int index);
    Chat *find(QString chatId);
signals:
    void scrolledToEnd() const;

private slots:
    void onDeleteSucceed();

private:
    QList<Chat*> m_List;

};

#endif // CHATLISTMODEL_H
