#ifndef COLORLISTMODEL_H
#define COLORLISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<materialcolor.h>
#include<materialcolors.h>
#include<qdebug.h>

class ColorListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ColorListModel(QObject *parent = nullptr);
    enum ColorRoles{
        ColorRole=Qt::UserRole+1,
    };

    QHash<int,QByteArray> roleNames() const;
    QVariant data(const QModelIndex &index,int role) const;
    int rowCount(const QModelIndex &parent=QModelIndex()) const;

    bool removeRows(int row=0, int count=0, const QModelIndex &parent=QModelIndex());

    void append(MaterialColor* e);
signals:
    void scrolledToEnd() const;

private slots:
    bool onDeleteSucceed();

private:
    QList<MaterialColor*> m_List;
};

#endif // COLORLISTMODEL_H
