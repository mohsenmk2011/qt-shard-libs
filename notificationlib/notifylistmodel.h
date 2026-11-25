#ifndef INTRODUCELISTMODEL_H
#define INTRODUCELISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<notify.h>

class NotifyListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit NotifyListModel(QObject *parent = nullptr);
    enum NotifyRoles{
        NotifyIdRole=Qt::UserRole+1,
        NotifyImageUrlRole=Qt::UserRole+2,
        NotifyTitleRole=Qt::UserRole+3,
        NotifyDescriptionRole=Qt::UserRole+4,
        NotifyRole=Qt::UserRole+5,
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;
    bool removeRows(int row=0,int count=0,const QModelIndex & parent=QModelIndex());

    void addItem(Notify* i);
    Q_INVOKABLE Notify* get(int index);
signals:
    void scrolledToEnd() const;

public slots:
    void removeItem();
private:
    QList<Notify*> m_Notifies;
};

#endif // INTRODUCELISTMODEL_H
