#include "order.h"

Order::Order(QObject *parent) : JooyaNetwork(parent)
{
    setId(0);
    setDiscountPercent(0);
    setDate("");
    setPrice(0);
    setPriceWithDiscount(0);
    setPaid(false);
    setManualPaid(false);
    setManualPaymentReceipt("");
    setUserId("");
    //if user has tried for payment read the order id from settings
    ApplicationSettings as;
    if(!(as.lastTriedPaymentOrderId().isNull()||as.lastTriedPaymentOrderId().isEmpty())){
        AndroidDeepLinkManager::m_OrderId = as.lastTriedPaymentOrderId().toInt();
    }
}

Order::Order(int id, QString date, int price,bool mp, bool paid, QString userId):Order()
{
    setId(id);
    setDate(date);
    setPrice(price);
    setPaid(paid);
    setManualPaid(mp);
    setUserId(userId);
}

int Order::id()
{
    return m_Id;
}

int Order::price()
{
    return m_Price;
}

QString Order::date()
{
    return m_Date;
}

bool Order::paid()
{
    return m_Paid;
}

QString Order::userId()
{
    return m_UserId;
}

bool Order::manualPaid()
{
    return m_ManualPaid;
}

void Order::setManualPaid(bool p)
{
    if(m_ManualPaid!=p){
        m_ManualPaid=p;
        emit manualPaidChanged();
    }
}

void Order::setId(int id)
{
    if(m_Id!=id){
        m_Id=id;
        emit idChanged();
    }
}

void Order::setPrice(int price)
{
    if(m_Price!=price){
        m_Price=price;
        emit priceChanged();
    }
}

void Order::setDate(QString date)
{
    if(m_Date!=date){
        m_Date=date;
        emit dateChanged();
    }
}

void Order::setPaid(bool paid)
{
    if(m_Paid!=paid){
        m_Paid=paid;
        emit paidChanged();
    }
}

void Order::setUserId(QString userId)
{
    if(m_UserId!=userId){
        m_UserId=userId;
        emit userIdChanged();
    }
}

QString Order::convertPriceToText(int price)
{    
    return QString("%1 تومان").arg(price/10);
}

bool Order::hasDiscount()
{
    return m_HasDiscount;
}

void Order::setHasDiscount(bool hd)
{
    if(m_HasDiscount!=hd){
        m_HasDiscount=hd;
        emit hasDiscountChanged();
    }
}

int Order::priceWithDiscount()
{
    return m_PriceWithDiscount;
}

void Order::setPriceWithDiscount(int p)
{
    if(m_PriceWithDiscount!=p){
        m_PriceWithDiscount=p;
        emit priceWithDiscountChanged();
    }
}

int Order::discountPercent()
{
    return m_DiscountPercent;
}

void Order::setDiscountPercent(int percent)
{
    if(m_DiscountPercent!=percent){
        m_DiscountPercent=percent;
        emit dicountPercentChanged();
    }
}

void Order::load(QString userId)
{
    QNetworkReply* r= getRequest(QString("api/Order?userId=%1").arg(userId));
    connect(r,SIGNAL(finished()),this,SLOT(loadFinished()));
}

void Order::loadFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        readOrder(r->readAll());
        //if payment not paid and has billId so get the result of payment
        if(!paid()&&!(billId().isNull()||billId().isEmpty()))
        {
            getPaymentResult();
        }
    }
    else{
        showMessage(r);
    }
    setIsProcssing(false);
}

void Order::getPaymentResult(int orderid)
{
    if(orderid<=0){
        orderid = id();
    }
    QNetworkReply* r= getRequest(QString("api/Order/Result/%1").arg(orderid));
    connect(r,SIGNAL(finished()),this,SLOT(getPaymentResultFinished()));

}
void Order::getPaymentResultFinished()
{
    QNetworkReply* r= convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        setPaid(true);
    }
    else{
        showBadMessage(r->readAll());
    }
    qDebug()<<"reset the last order id that user tried for payment";
    ApplicationSettings as;
    as.setLastTriedPaymentOrderId("");
}

void Order::saveManualPaymentReceiptFinished()
{
    QNetworkReply* r= convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        showOkMessage(r->readAll());
    }
    else{
        showBadMessage(r->readAll());
    }
}

void Order::manualPay()
{
    setIsProcssing(true);
    QNetworkReply* r=getRequest(QString("api/Order/ManualPay/%1").arg(id()));
    connect(r,SIGNAL(finished()),this,SLOT(manualPayFinished()));
}

void Order::saveManualPaymentReceipt()
{
    if(manualPaymentReceipt().isNull()){
        message()->setContent("رسید پرداخت را وارد کنید");
        return;
    }
    setIsProcssing(true);
    QNetworkReply* r=postRequest("api/Order",readManualPaymentReceipt());
    connect(r,SIGNAL(finished()),this,SLOT(saveManualPaymentReceiptFinished()));

}
void Order::manualPayFinished()
{
    QNetworkReply* r=convertToReply(sender());
    if(r->error()==QNetworkReply::NoError){
        setManualPaid(!manualPaid());
    }
    showMessage(r);
    setIsProcssing(false);
}


void Order::readOrder(QByteArray json)
{
    qDebug()<<"order=> "<<json;
    QJsonDocument doc= QJsonDocument::fromJson(json);
    QJsonObject obj= doc.object();
    setId(obj.value("id").toInt());
    setDate(obj.value("date").toString());
    setPaid(obj.value("paid").toBool());
    setBillId(obj.value("billId").toString());
    setManualPaid(obj.value("manualPaid").toBool());
    qDebug()<<"manualPaid="<<manualPaid();
    setPrice(obj.value("price").toInt());
    setUserId(obj.value("userId").toString());
    setPriceWithDiscount(obj.value("priceWithDiscount").toInt());
    setDiscountPercent(obj.value("discountPercent").toInt());
    setHasDiscount(obj.value("hasDiscount").toBool());
    setManualPaymentReceipt(obj.value("manualPaymentReceipt").toString());
}

QJsonObject Order::readManualPaymentReceipt()
{
    QJsonObject obj;
    obj.insert("id",id());
    obj.insert("manualPaymentReceipt",manualPaymentReceipt());
    return obj;
}


const QString &Order::billId() const
{
    return m_billId;
}

void Order::setBillId(const QString &newBillId)
{
    if (m_billId == newBillId)
        return;
    m_billId = newBillId;
    emit billIdChanged();
}

QString Order::manualPaymentReceipt() const
{
    return m_manualPaymentReceipt;
}

void Order::setManualPaymentReceipt(const QString &newManualPaymentReceipt)
{
    if (m_manualPaymentReceipt == newManualPaymentReceipt)
        return;
    m_manualPaymentReceipt = newManualPaymentReceipt;
    emit manualPaymentReceiptChanged();
}
