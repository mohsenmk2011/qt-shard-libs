#include "keyword.h"

Keyword::Keyword(QObject *parent) : JooyaNetwork(parent)
{
    setKeywordId(0);
    setParentId(0);
    setSelected(false);
    setValue("کلمه کلیدی جدید");
}

Keyword::Keyword(int parentId):Keyword()
{
    setParentId(parentId);
}

Keyword::Keyword(QJsonObject json)
{
    loadFromJson(json);
}

void Keyword::loadFromJson(QJsonObject json)
{
    setKeywordId(json.value("id").toInt());
    setParentId(json.value("parentId").toInt());
    setValue(json.value("value").toString());
    setSelected(json.value("selected").toBool());
    qInfo()<<"selected==>"<<selected();
}

int Keyword::keywordId()
{
    return m_KeywordId;
}

void Keyword::setKeywordId(int kId)
{
    if(m_KeywordId!=kId){
        m_KeywordId=kId;
        emit keywordIdChanged();
    }
}

int Keyword::parentId()
{
    return m_ParentId;
}

void Keyword::setParentId(int pId)
{
    if(m_ParentId!=pId){
        m_ParentId=pId;
        emit parentIdChanged();
    }
}

QString Keyword::value()
{
    return m_Value;
}

void Keyword::setValue(QString v)
{
    if(m_Value!=v){
        m_Value=v;
        emit valueChanged();
    }
}

bool Keyword::selected()
{
    return m_Selected;
}

void Keyword::setSelected(bool s)
{
    if(m_Selected!=s){
        m_Selected=s;
        emit selectedChanged();
    }
}

void Keyword::save()
{
    setIsProcssing(true);
    if(!isFeildsValid()){
        return;
    }
    qInfo()<<"save Keyword";

    QNetworkReply* r=postRequest("api/Keyword",convertToJson());
    connect(r,SIGNAL(finished()),this,SLOT(saveFinished()));
}

bool Keyword::isFeildsValid(){
    if(value().isNull()||value().isEmpty()){
        message()->setContent("نام کلمه کلیدی را وارد کنید");
        return false;
    }
    return true;
}

void Keyword::deleteItem()
{
    if(keywordId()==0){
        emit deleteSucceed();
        message()->setContent("حذف شد");
        return;
    }
    QNetworkReply* r=deleteRequest("api/Keyword/"+QString::number(keywordId()));
    connect(r,SIGNAL(finished()),this,SLOT(deleteItemFinished()));
}

void Keyword::deleteItemFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        emit deleteSucceed();
    }
    showMessage(r);
    setIsProcssing(false);
}

void Keyword::saveFinished()
{
    qInfo()<<"Save Keyword Finished";
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError)
    {
        qInfo()<<"With NO Error";
        QJsonObject obj=jsonUtility()->convertToJsonObject(r);
        showOkMessage(obj.value("message").toString());
        QString SId=obj.value("id").toString();
        qInfo()<<"KeywordId now is => "<<SId.toInt();
        setKeywordId(SId.toInt());
        qInfo()<<"KeywordId now is => "<<keywordId();

        emit saveSucceed();
    }
    else {
        qCritical()<<"With Error";
        showMessage(r);
    }
    setIsProcssing(false);
}

QJsonObject Keyword::convertToJson()
{
    QJsonObject obj;
    obj.insert("id",keywordId());
    obj.insert("value",value());
    if(parentId()>0){
        obj.insert("parentId",parentId());
    }
    obj.insert("selected",selected());
    return obj;
}
