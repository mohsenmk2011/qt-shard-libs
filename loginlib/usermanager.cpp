#include "usermanager.h"

UserManager::UserManager(QObject *parent) : ListManager(parent)
{
    setTakeCount(15);
    connect(&m_ListModel,SIGNAL(scrolledToEnd()),this,SLOT(getList()));
}

void UserManager::getList()
{
    if(listHasCompeleted()||isProcessing())
    {
        qInfo()<<"listHasCompeleted => "<<listHasCompeleted();
        qInfo()<<"isProcessing => "<<isProcessing();
        return;
    }
    setIsProcssing(true);
    QString url=QString("api/User?skipcount=%1&count=%2").arg(skipCount()).arg(takeCount());
    QNetworkReply* r=getRequest(url);
    connect(r,SIGNAL(finished()),this,SLOT(getListFinishded()));
}

void UserManager::getListFinishded()
{
    QNetworkReply* reply=convertToReply(sender());
    qDebug()<<"get User ListFinishded";
    if(reply->error()==QNetworkReply::NoError)
    {
        QString response=reply->readAll();
        qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        qDebug()<<"=>NoError)";
        qDebug()<<response;
        qDebug()<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        QJsonDocument jdoc=QJsonDocument::fromJson(response.toUtf8());
        QJsonArray array=jdoc.array();
        QList<User*> lb;
        //        if(isSearch())
        //        {
        //            m_list.removeRows();
        //        }
        for (int i = 0; i < array.count(); ++i) {
            QJsonValue value=array.at(i);
            QJsonObject obj=value.toObject();

            User* b=new User(obj.value("id").toString(),obj.value("userName").toString(),obj.value("registerDate").toString());
            lb.append(b);
            m_ListModel.addUser(b);
        }
        setLastTakedCount(lb.count());
    }
    else if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==404)
    {
        setListHasCompeleted(true);
        if(m_ListModel.rowCount()<=0)
        {
            message()->setContent("کاربری یافت نشد");
        }
    }
    else
    {
        showMessage(reply);
    }
    setIsProcssing(false);

}

UserListModel *UserManager::listModel()
{
    return &m_ListModel;
}
