#include "postbase.h"

PostBase::PostBase(QObject *parent)
    : JooyaListItem{parent}
{
    m_IsJustDate=false;
    m_FromMe=false;
    m_Id=QUuid::createUuid().toString(QUuid::StringFormat::WithoutBraces);
    m_Date=QDateTime::currentDateTime();
    m_PersianDateTime=new PersianDateTime(m_Date);
    m_ResendingStatusRequestDone=false;
    m_Status=TalkStatus::TalkStatusEnum::NotSend;
}

PostBase::PostBase(QDateTime date, bool isJustDate):PostBase()
{
    setDate(date);
    setIsJustDate(isJustDate);
}

QString PostBase::id()
{
    return m_Id;
}

void PostBase::setId(QString id)
{
    if(m_Id!=id){
        m_Id=id;
        emit idChanged();
    }
}

QString PostBase::chatId()
{
    return m_ChatId;
}

void PostBase::setChatId(QString cId)
{
    if(m_ChatId!=cId){
        m_ChatId=cId;
        emit chatIdChanged();
    }
}

QString PostBase::content()
{
    return m_Content;
}

void PostBase::setContent(QString c)
{
    if(m_Content!=c){
        m_Content=c;
        emit contentChanged();
    }
}

QString PostBase::userId()
{
    return m_UserId;
}

void PostBase::setUserId(QString uId)
{
    if(m_UserId!=uId){
        m_UserId=uId;
        emit userIdChanged();
    }
}

QDateTime PostBase::date()
{
    return m_Date;
}

void PostBase::setDate(QDateTime d)
{
    if(m_Date!=d){
        m_Date=d;
        updatedateText();
        m_PersianDateTime->setDate(d);
        emit dateChanged();
    }
}

TalkStatus::TalkStatusEnum PostBase::status()
{
    return m_Status;
}

void PostBase::setStatus(TalkStatus::TalkStatusEnum s)
{
    if(s>m_Status){
        m_Status=s;
        if(s==TalkStatus::TalkStatusEnum::Send){
            emit postSendSucceed();
        }
        setWaitingForResendStatus(false);
        emit statusChanged();
    }
}

bool PostBase::waitingForResendStatus(){
    return m_ResendingStatusRequestDone;
}

void PostBase::setWaitingForResendStatus(bool w){
    m_ResendingStatusRequestDone=w;
}

QString PostBase::hour()
{
//    return dateTimeUtility()->toPersianHourString(date());
    return m_PersianDateTime->shortTime();
}

QString PostBase::persianDate()
{
    return m_PersianDateTime->shortDate();
}

QString PostBase::dateText()
{
    return m_DateText;
}

void PostBase::setDateText(QString d)
{
    if(m_DateText!=d){
        m_DateText=d;
        emit dateTextChanged();
    }
}

void PostBase::updatedateText()
{
    QString t="";
    int days=date().daysTo(QDateTime::currentDateTime());
    qInfo()<<"days to today is => "<<days;
    if(days<=0){
        t= "امروز";
    }
    else if (days==1) {
        t= "دیروز";
    }
    else if (days==2) {
        t= "پریروز";
    }
    else {
        t= persianDate();
    }
    setDateText(t);
}

int PostBase::topMargin()
{
    return m_TopMargin;
}

void PostBase::setTopMargin(int m)
{
    if(m_TopMargin!=m){
        m_TopMargin=m;
        emit topMarginChanged();
    }
}

bool PostBase::fromMe()
{
    return m_FromMe;
}

void PostBase::setFromMe(bool me)
{
    if(m_FromMe!=me){
        m_FromMe=me;
        emit fromMeChanged();
    }
}

bool PostBase::isJustDate()
{
    return m_IsJustDate;
}

void PostBase::setIsJustDate(bool i)
{
    if(m_IsJustDate!=i){
        m_IsJustDate=i;
        emit isJustDateChanged();
    }
}

void PostBase::send(QString contactId)
{

}
