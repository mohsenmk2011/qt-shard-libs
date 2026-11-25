#include "colorlistmodel.h"

ColorListModel::ColorListModel(QObject *parent) : QAbstractListModel(parent)
{
    m_List={};
    for (int i = 0; i < 20; ++i) {
        m_List.append(new MaterialColor(static_cast<MaterialColors::MaterialColorsEnum>(i)));
    }
    qInfo()<<"m_List.count() color count"<<m_List.count();
}

QHash<int, QByteArray> ColorListModel::roleNames() const
{
    QHash<int,QByteArray> roles;
    roles[ColorRole]="model";
    return roles;
}

QVariant ColorListModel::data(const QModelIndex &index, int role) const
{
    int i=index.row();
    if(i<0||i>=m_List.size())
    {
        return QVariant(QVariant::Invalid);
    }
    else if(i==m_List.count()-1){
        emit scrolledToEnd();
    }

    MaterialColor *entity =m_List[i];
    if(role==ColorRole){
        return QVariant::fromValue(entity);
    }
    else {
        return QVariant();
    }
}

int ColorListModel::rowCount(const QModelIndex &parent) const
{
    return m_List.count();
}

bool ColorListModel::removeRows(int row, int count, const QModelIndex &parent)
{
    int c=rowCount();
    if(c<=0){
        return  true;
    }
    beginRemoveRows(QModelIndex(),0,c-1);
    for (int i = 0; i <c&&rowCount()>0 ; ++i) {
        m_List.removeAt(0);
    }
    endRemoveRows();
    return true;

}

void ColorListModel::append(MaterialColor *e)
{
    //ToDo: if exsits don't insert multiple time
    for (int i = 0; i < rowCount(); ++i) {
        MaterialColor* color= m_List.at(i);
        if(color->color()==e->color()){
            return;
        }
    }
    beginInsertRows(QModelIndex(),rowCount(),rowCount());
    m_List<< e;
    endInsertRows();
    connect(e,SIGNAL(deleteSucceed()),this,SLOT(onDeleteSucceed()));
}

bool ColorListModel::onDeleteSucceed()
{
    if(rowCount()<=0){
        return  true;
    }
    MaterialColor* cc=qobject_cast<MaterialColor*>(sender());
    for (int i = 0; i <rowCount()&&rowCount()>0 ; ++i) {
        if(m_List.at(i)->color()==cc->color()){
            beginRemoveRows(QModelIndex(),i,i);
            m_List.removeAt(i);
            endRemoveRows();
            break;
        }
    }
    return true;
}
