#ifndef KEYWORDTYPELISTMODEL_H
#define KEYWORDTYPELISTMODEL_H

#include <QObject>
#include<keywordtype.h>
#include<QAbstractListModel>
#include<qdebug.h>
#include<QJsonDocument>
#include<QJsonArray>
#include<QJsonValue>
#include<QJsonObject>

class KeywordTypeListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit KeywordTypeListModel(QObject *parent = nullptr);

    enum KeywordTypeRoles{
        KeywordTypeRole=Qt::UserRole+1
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void add(KeywordType* e);
    void edit(int id, QString name);
    void edit(KeywordType *e);
    void loadFromResponse(QString response);
    Keyword *find(int keywordId);
signals:
    void scrolledToEnd() const;
private slots:
    void itemHasRemoved();
private:
    QList<KeywordType*> m_List;

};

#endif // KEYWORDTYPELISTMODEL_H
