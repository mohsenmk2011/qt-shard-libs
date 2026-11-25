#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include<jooyanetwork.h>
#include<applicationsettings.h>
#include<androiddeeplinkmanager.h>

class Order : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(int id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString billId READ billId WRITE setBillId NOTIFY billIdChanged)
    Q_PROPERTY(int price READ price WRITE setPrice NOTIFY priceChanged)
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(bool paid READ paid WRITE setPaid NOTIFY paidChanged)
    Q_PROPERTY(bool manualPaid READ manualPaid WRITE setManualPaid NOTIFY manualPaidChanged)
    Q_PROPERTY(QString userId READ userId WRITE setUserId NOTIFY userIdChanged)
    Q_PROPERTY(bool hasDiscount READ hasDiscount WRITE setHasDiscount NOTIFY hasDiscountChanged)
    Q_PROPERTY(int priceWithDiscount READ priceWithDiscount WRITE setPriceWithDiscount NOTIFY priceWithDiscountChanged)
    Q_PROPERTY(int discountPercent READ discountPercent WRITE setDiscountPercent NOTIFY dicountPercentChanged)
    Q_PROPERTY(QString manualPaymentReceipt READ manualPaymentReceipt WRITE setManualPaymentReceipt NOTIFY manualPaymentReceiptChanged)

public:
    explicit Order(QObject *parent = nullptr);    
    Order(int id, QString date, int price, bool mp, bool paid, QString userId);

    int id();
    int price();
    QString date();

    bool paid();
    QString userId();

    bool manualPaid();
    void setManualPaid(bool p);

    void setId(int id);
    void setPrice(int price);
    void setDate(QString date);
    void setPaid(bool paid);
    void setUserId(QString userId);
    Q_INVOKABLE QString convertPriceToText(int price);

    bool hasDiscount();
    void setHasDiscount(bool hd);

    int priceWithDiscount();
    void setPriceWithDiscount(int p);

    int discountPercent();
    void setDiscountPercent(int percent);
    //==========
    Q_INVOKABLE void load(QString userId);
    Q_INVOKABLE void getPaymentResult(int orderid=0);
    Q_INVOKABLE void manualPay();
    Q_INVOKABLE void saveManualPaymentReceipt();

    const QString &billId() const;
    void setBillId(const QString &newBillId);

    QString manualPaymentReceipt() const;
    void setManualPaymentReceipt(const QString &newManualPaymentReceipt);

signals:
    void idChanged();
    void priceChanged();
    void dateChanged();
    void paidChanged();
    void manualPaidChanged();
    void userIdChanged();
    void hasDiscountChanged();
    void priceWithDiscountChanged();
    void dicountPercentChanged();
    void billIdChanged();
    void manualPaymentReceiptChanged();

private:
    int m_Id;
    int m_Price;
    int m_DiscountPercent;
    QString m_Date;
    bool m_Paid;
    bool m_ManualPaid;
    QString m_UserId;
    bool m_HasDiscount;
    int m_PriceWithDiscount;
    void readOrder(QByteArray json);
    QString m_billId;

    QString m_manualPaymentReceipt;
    QJsonObject readManualPaymentReceipt();

private slots:
    void loadFinished();
    void manualPayFinished();
    void getPaymentResultFinished();
    void saveManualPaymentReceiptFinished();
};

#endif // ORDER_H
