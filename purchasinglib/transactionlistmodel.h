#ifndef TRANSACTIONLISTMODEL_H
#define TRANSACTIONLISTMODEL_H

#include <QObject>
#include<QAbstractListModel>
#include<transaction.h>

class TransactionListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit TransactionListModel(QObject *parent = nullptr);
    enum TransactionRoles{
        TransactionRole=Qt::UserRole+1
    };

    int rowCount(const QModelIndex &parent= QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    void add(Transaction *t);
    QHash<int, QByteArray> roleNames() const;
signals:

public slots:
private:
    QList<Transaction*> m_Transactions;
};

#endif // TRANSACTIONLISTMODEL_H
