#ifndef USERIMAGELISTMODEL_H
#define USERIMAGELISTMODEL_H

#include <QObject>
#include<userimage.h>
#include<QAbstractListModel>

class UserImageListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit UserImageListModel(QObject *parent = nullptr);
    enum UserImageRoles{
        UserImageRole=Qt::UserRole+1
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());
    bool removeAt(int index);

    void add(UserImage *u);
    void insert(UserImage *u,int index=0);
    Q_INVOKABLE UserImage *get(int index);

    void removeDefualts();

signals:
    void scrolledToEnd() const;
    void deletedItem();

private slots:
    bool deleteItem();
private:
    QList<UserImage*> m_List;
};

#endif // USERIMAGELISTMODEL_H
