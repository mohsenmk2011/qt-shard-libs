#ifndef POSTLISTMODEL_H
#define POSTLISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<post.h>

class PostListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Post* selectedPost READ selectedPost CONSTANT)
public:
    explicit PostListModel(QObject *parent = nullptr);
    enum PostRoles{
        PostRole=Qt::UserRole+1,
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void append(Post* t,bool insertDateRow=true);
    Post *at(int index);
    Post *find(QString id);
    void removeById(QString id);
    int unReadTalksCount();

    Post* selectedPost();
signals:
    void scrolledToEnd() const;

private slots:
    bool onDeleteSucceed();

private:
    QList<Post*> m_List;
    void updateDateRows(Post* newTalk);

};

#endif // POSTLISTMODEL_H
