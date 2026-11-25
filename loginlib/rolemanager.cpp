#include "rolemanager.h"

RoleManager::RoleManager(QObject *parent) : JooyaNetwork(parent)
{
}

void RoleManager::getList()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest("api/Role");
    connect(r,SIGNAL(finished()),this,SLOT(getListFinished()));
}

RoleListModel* RoleManager::listModel()
{
    return &m_ListModel;
}

void RoleManager::add()
{
    m_ListModel.addRole(new Role());
}

void RoleManager::getListFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QString result=r->readAll();
        m_ListModel.loadFromResponse(result);
    }
    else if(r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt()==404)
    {
        if(m_ListModel.rowCount()<=0)
        {
            message()->setContent("نقشی یافت نشد");
        }
    }
    else {
        showMessage(r);
    }
    setIsProcssing(false);
}
