#ifndef CAFEBAZARPAYMENTMANAGER_H
#define CAFEBAZARPAYMENTMANAGER_H

#include <QObject>
#include <QString>
#include <QtDebug>
#include <jooyanetwork.h>
#include <paymentresult.h>

#if defined(Q_OS_ANDROID)
#include <QCoreApplication>
#include <QJniEnvironment>
#include <QJniObject>
#include <packageinfomanager.h>
#endif

/**
 * @brief Cafe Bazaar in-app billing bridge for the Qt application.
 *
 * Android: calls CafeBazaarManager.java (which uses the Cafe Bazaar IabHelper SDK)
 * through JNI to start the Bazaar purchase UI. The Java side calls back
 * CafeBazaarManager.sendPurchaseResultToQtApp(token, sku, success, message).
 *
 * On success this class calls the backend api/Order/VerifyCafebazaar so the
 * purchase token is validated server-side before the order is marked paid.
 *
 * Desktop: startPurchase() is a stub that emits purchaseFailed(...).
 */
class CafebazaarPaymentManager : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(int orderId READ orderId WRITE setOrderId NOTIFY orderIdChanged)
    Q_PROPERTY(PaymentResult* paymentResult READ paymentResult NOTIFY paymentResultChanged)

public:
    explicit CafebazaarPaymentManager(QObject *parent = nullptr);

    static CafebazaarPaymentManager *instance() { return m_instance; }
    void registerNativesMethod();

    /// Requests the product SKU from the backend for the current order.
    Q_INVOKABLE void loadSku();
    /// Starts the Cafe Bazaar purchase UI for the given SKU.
    Q_INVOKABLE void startPurchase(QString sku);
    /// Called from the JNI callback (and usable from QML) to verify a purchase.
    Q_INVOKABLE void verifyPurchase(QString purchaseToken, QString sku);

    int orderId() const;
    void setOrderId(int orderId);

    PaymentResult* paymentResult();

signals:
    /// Emitted when the backend returns the SKU to purchase.
    void skuReceived(QString sku);
    /// Emitted when the native Bazaar purchase finished successfully.
    void purchaseSucceeded(QString purchaseToken, QString sku);
    /// Emitted when the native Bazaar purchase failed or was cancelled.
    void purchaseFailed(QString message);
    /// Emitted after the backend verifies the purchase.
    void purchaseVerified(bool paid);
    void orderIdChanged();
    void paymentResultChanged(PaymentResult* argPaymentResult);

private slots:
    void loadSkuFinished();
    void verifyPurchaseFinished();

private:
    static CafebazaarPaymentManager *m_instance;
    int m_orderId = 0;
    QString m_sku;
    PaymentResult* m_paymentResult;
};

#endif // CAFEBAZARPAYMENTMANAGER_H

