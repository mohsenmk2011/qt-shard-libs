#include "transaction.h"

Transaction::Transaction(QObject *parent) : QObject(parent)
{
    m_Id="";
    m_Date="";
    m_ResultMessage="";
    m_ShenasehErja="";
    m_Dargah="";
    m_CreditCardNumber="";
}
Transaction::Transaction(QString id,QString date,QString resultMessage,QString shenasehErja,QString dargah,QString creditCardNumber) :Transaction()
{
    setId(id);
    setDate(date);
    setResultMessage(resultMessage);
    setShenasehErja(shenasehErja);
    setDargah(dargah);
    setCreditCardNumber(creditCardNumber);
}


QString Transaction::id()
{
    return m_Id;
}

void Transaction::setId(QString i)
{
    if(m_Id!=i){
        m_Id=i;
        emit idChanged();
    }
}

QString Transaction::date()
{
    return m_Date;
}

void Transaction::setDate(QString d)
{
    if(m_Date!=d){
        m_Date=d;
        emit dateChanged();
    }
}

QString Transaction::resultMessage()
{
    return m_ResultMessage;
}

void Transaction::setResultMessage(QString r)
{
    if(m_ResultMessage!=r){
        m_ResultMessage=r;
        emit resultMessageChanged();
    }
}

QString Transaction::shenasehErja()
{
    return m_ShenasehErja;
}

void Transaction::setShenasehErja(QString s)
{
    if(m_ShenasehErja!=s){
        m_ShenasehErja=s;
        emit shenasehErjaChanged();
    }
}

QString Transaction::dargah()
{
    return m_Dargah;
}

void Transaction::setDargah(QString d)
{
    if(m_Dargah!=d){
        m_Dargah=d;
        emit dargahChanged();
    }
}

QString Transaction::creditCardNumber()
{
    return m_CreditCardNumber;
}

void Transaction::setCreditCardNumber(QString c)
{
    if(m_CreditCardNumber!=c){
        m_CreditCardNumber=c;
        emit creditCardNumberChanged();
    }
}
