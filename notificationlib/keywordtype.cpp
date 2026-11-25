#include "keywordtype.h"

KeywordType::KeywordType(QObject *parent) : JooyaNetwork(parent)
{
    m_KeywordTypeId=0;
    m_Value="بی نام";
}

KeywordType::KeywordType(int id, QString value)
{
    setKeywordTypeId(id);
    setValue(value);
}

KeywordType::KeywordType(QJsonObject obj)
{
    loadFromJson(obj);
}

QString KeywordType::value()
{
    return m_Value;
}

void KeywordType::setValue(QString v)
{
    if(m_Value!=v){
        m_Value=v;
        emit valueChanged();
    }
}

int KeywordType::keywordTypeId()
{
    return m_KeywordTypeId;
}

void KeywordType::setKeywordTypeId(int ktId)
{
    if(ktId!=m_KeywordTypeId){
        m_KeywordTypeId=ktId;
        emit keywordTypeIdChanged();
    }
}

void KeywordType::loadFromJson(QJsonObject obj)
{
   setKeywordTypeId(obj.value("id").toInt());
   setValue(obj.value("value").toString());
   QJsonArray ks=obj.value("keywords").toArray();
   qWarning()<<"&&& keywords.count= "<<ks.count()<<" &&&";

   for (int i = 0; i < ks.count(); ++i) {
       keywords()->add(new Keyword(ks.at(i).toObject()));
   }
}

KeywordListModel *KeywordType::keywords()
{
    return &m_Keywords;
}

void KeywordType::deleteItem()
{
    if(keywordTypeId()==0){
        emit deleteSucceed();
        message()->setContent("حذف شد");
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=deleteRequest("api/KeywordType/"+QString::number(keywordTypeId()));
    connect(r,SIGNAL(finished()),this,SLOT(deleteItemFinished()));
}

void KeywordType::deleteItemFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        emit deleteSucceed();
    }
    else {
        showMessage(r);
    }
    setIsProcssing(false);
}

QJsonObject KeywordType::convertToJson()
{
    QJsonObject obj;
    obj.insert("value",value());
    obj.insert("id",keywordTypeId());
    return obj;
}

void KeywordType::save()
{
    setIsProcssing(true);
    QNetworkReply* r=postRequest("api/KeywordType",convertToJson());
    connect(r,SIGNAL(finished()),this,SLOT(saveFinished()));
}

void KeywordType::addNewKeyword()
{
    m_Keywords.add(new Keyword(keywordTypeId()));
}

void KeywordType::saveFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        QJsonObject obj=jsonUtility()->convertToJsonObject(r);
        showOkMessage(obj.value("message").toString());
        if(keywordTypeId()==0){
            setKeywordTypeId(obj.value("id").toInt());
        }
        emit saveSucceed();
    }
    else{
        showMessage(r);
    }
    setIsProcssing(false);
}
