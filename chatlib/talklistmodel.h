#ifndef TALKLISTMODEL_H
#define TALKLISTMODEL_H

#include <QObject>
#include<post.h>
#include<QAbstractListModel>
#include<qdebug.h>

class TalkListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TalkListModel(QObject *parent = nullptr);
    enum TalkRoles{
        TalkRole=Qt::UserRole+1,
    };


    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    int unReadTalksCount();

    void add(Post* t);
    Post *get(int index);
    Post *find(QString id);
    void removeById(QString id);
signals:
    void scrolledToEnd() const;

private slots:
    bool onDeleteSucceed();

private:
    QList<Post*> m_List;
    void updateDateRows(Post* newTalk);
};

#endif // TALKLISTMODEL_H
