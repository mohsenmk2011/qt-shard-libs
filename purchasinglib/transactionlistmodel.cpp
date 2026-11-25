#include "transactionlistmodel.h"

TransactionListModel::TransactionListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_Transactions={};
}

int TransactionListModel::rowCount(const QModelIndex &parent) const{
    return m_Transactions.size();
}

QVariant TransactionListModel::data(const QModelIndex &index, int role) const{
    int i=index.row();
    if(i<0||i>rowCount()){
        return QVariant(QVariant::Invalid);
    }
   if(role==TransactionRole){
       return QVariant::fromValue(m_Transactions[i]);
   }
   else {
       return QVariant(QVariant::Invalid);
   }
}

void TransactionListModel::add(Transaction* t){
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_Transactions<<t;
    endInsertRows();
}

QHash<int,QByteArray> TransactionListModel::roleNames() const{
    QHash<int,QByteArray> roles;
    roles[TransactionRole]="currentTransaction";
    return roles;
}
