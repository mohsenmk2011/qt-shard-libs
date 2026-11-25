#include "paymentresult.h"

PaymentResult::PaymentResult(QObject *parent) : QObject(parent)
{
    m_Paid=false;
    setTrackingCode("0");
    setMessage("در حال دریافت نتیجه تراکنش");
}

PaymentResult::PaymentResult(bool p, QString tc):PaymentResult()
{
    setPaid(p);
    setTrackingCode(tc);
}

bool PaymentResult::paid()
{
    return m_Paid;
}

void PaymentResult::setPaid(bool p)
{
    if(m_Paid!=p)
    {
        m_Paid=p;
        emit paidChanged();
    }
    if(p){
        setMessage("پرداخت موفقیت آمیز بود");
    }
    else {

        setMessage("پرداخت موفقیت آمیز نبود");
    }
}

QString PaymentResult::trackingCode()
{
    return m_TrackingCode;
}

void PaymentResult::setTrackingCode(QString tc)
{
    if(m_TrackingCode!=tc){
        m_TrackingCode=tc;
        emit trackingCodeChanged();
    }
}

QString PaymentResult::message()
{
    return m_Message;
}

void PaymentResult::setMessage(QString m)
{
    if(m_Message!=m){
        m_Message=m;
        emit messageChanged();
    }
}
