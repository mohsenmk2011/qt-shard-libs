#ifndef KEYWORDLISTMODEL_H
#define KEYWORDLISTMODEL_H

#include <QObject>
#include<keyword.h>
#include<QAbstractListModel>
#include<qdebug.h>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonValue>
#include<QJsonObject>

class KeywordListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit KeywordListModel(QObject *parent = nullptr);

    enum KeywordRoles{
        KeywordRole=Qt::UserRole+1
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void add(Keyword* e);
    void edit(int id, QString value);
    void edit(Keyword *e);
    void loadFromResponse(QString response);
    Keyword *find(int keywordId);
signals:
    void scrolledToEnd() const;
private slots:
    void itemHasRemoved();
private:
    QList<Keyword*> m_List;

};

#endif // KEYWORDLISTMODEL_H
