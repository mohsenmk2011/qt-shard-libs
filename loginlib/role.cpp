#include "role.h"

Role::Role(QObject *parent) : JooyaNetwork(parent)
{
    m_Id="";
    m_Name="RoleName";
    m_Selected=false;
}

Role::Role(QString name,QString id,bool selected):Role()
{
    setName(name);
    setId(id);
    setSelected(selected);
}

QString Role::id()
{
    return  m_Id;
}

void Role::setId(QString id)
{
    if(m_Id!=id){
        m_Id=id;
        emit idChanged();
    }
}

QString Role::name()
{
    return  m_Name;
}

void Role::setName(QString id)
{
    if(m_Name!=id){
        m_Name=id;
        emit nameChanged();
    }
}

bool Role::selected()
{
    return  m_Selected;
}

void Role::setSelected(bool id)
{
    if(m_Selected!=id){
        m_Selected=id;
        emit selectedChanged();
    }
}

void Role::save()
{
    if(name().isNull()||name().isEmpty()){
        message()->setContent("نام نقش را وارد کنید");
        return;
    }
    setIsProcssing(true);
    QJsonObject obj;
    obj.insert("Id",id());
    obj.insert("Name",name());
    QNetworkReply* r=postRequest("api/Role",obj);
    connect(r,SIGNAL(finished()),this,SLOT(saveFinished()));
}
void Role::saveFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QString response=r->readAll();
        qDebug()<<"response="<<response;
        QJsonDocument doc=QJsonDocument::fromJson(response.toUtf8());
        QJsonObject obj= doc.object();
        showOkMessage(obj.value("message").toString());
        if(id().isNull()||id().isEmpty()){
            setId(obj.value("stringId").toString());
        }
    }
    else{
        showMessage(r);
    }
    setIsProcssing(false);
}

void Role::deleteRole()
{
    qDebug()<<"is delteing role?";
    if(id().isNull()||id().isEmpty()){
        qDebug()<<"id is null ";
        emit deleted();        
        message()->setContent("حذف شد");
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=deleteRequest("api/Role/"+id());
    connect(r,SIGNAL(finished()),this,SLOT(deleteRoleFinished()));
}
void Role::deleteRoleFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        emit deleted();
    }
    showMessage(r);
    setIsProcssing(false);
}
