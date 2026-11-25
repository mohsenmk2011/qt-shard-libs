#ifndef PURCHASINGLIB_H
#define PURCHASINGLIB_H

#include<paymentresult.h>
#include<order.h>
#include<transaction.h>
#include<paymentmanager.h>
#include<cafebazaarpaymentmanager.h>
#include<QtQml/QQmlApplicationEngine>
class Purchasinglib
{
public:
    Purchasinglib();
    static void registerTypes()
    {
        qmlRegisterType<Order>("Jooya",1,0,"Order");
        qmlRegisterType<PaymentManager>("Jooya",1,0,"PaymentManager");
        qmlRegisterType<Transaction>("Jooya",1,0,"Transaction");
        qmlRegisterType<PaymentResult>("Jooya",1,0,"PaymentResult");
        qmlRegisterType<CafebazaarPaymentManager>("Jooya",1,0,"CafebazaarPaymentManager");
    }
};

#endif // PURCHASINGLIB_H
