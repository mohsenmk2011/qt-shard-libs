#include "signupresult.h"

SignupResult::SignupResult(QObject *parent) : QObject(parent)
{
    m_Timer.setInterval(1000);
    m_Time.setHMS(0,5,0,0);
    setMessage("کد فعالسازی را که دریافت کرده اید در کادر زیر وارد کنید");
    connect(&m_Timer,SIGNAL(timeout()),this,SLOT(timerTimeOut()));
}

QString SignupResult::timeToSendNext()
{
    return m_TimeSendNext;
}

void SignupResult::setTimeToSendNext(QString dId)
{
    if(m_TimeSendNext!=dId){
        m_TimeSendNext=dId;
        emit timeToSendNextChanged();
    }
}

QString SignupResult::message()
{
    return m_Message;
}

void SignupResult::setMessage(QString m)
{
    if(m_Message!=m){
        m_Message=m;
        emit messageChanged();
    }
}

QString SignupResult::phoneNumber()
{
    return m_PhoneNumber;
}

void SignupResult::setPhoneNumber(QString number)
{
    if(m_PhoneNumber!=number){
        m_PhoneNumber=number;
        emit phoneNumberChanged();
    }
}

int SignupResult::waitNextSms()
{
    return m_WaitNextSms;
}

void SignupResult::setWaitNextSms(int wait)
{
    if(m_WaitNextSms!=wait){
        m_WaitNextSms=wait;
        m_Time.setHMS(0,wait,0,0);
        emit waitNextSmsChanged();
    }
}

void SignupResult::startTimer()
{
    m_Timer.start();
}

void SignupResult::stopTimer()
{
    m_Timer.stop();
}

void SignupResult::timerTimeOut()
{
    m_Time= m_Time.addSecs(-1);
    setTimeToSendNext(m_Time.toString("m:ss"));
    if(m_Time.second()==0&&m_Time.minute()==0){
        m_Timer.stop();
        emit sendNextSms();
    }
}
