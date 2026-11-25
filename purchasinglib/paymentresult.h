#ifndef PAYMENTRESULT_H
#define PAYMENTRESULT_H

#include <QObject>

class PaymentResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool paid READ paid WRITE setPaid NOTIFY paidChanged)
    Q_PROPERTY(QString trackingCode READ trackingCode WRITE setTrackingCode NOTIFY trackingCodeChanged)
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged)
public:
    explicit PaymentResult(QObject *parent = nullptr);
    PaymentResult(bool p,QString tc);

    bool paid();
    void setPaid(bool p);

    QString trackingCode();
    void setTrackingCode(QString tc);

    QString message();
    void setMessage(QString m);


signals:
    void paidChanged();
    void trackingCodeChanged();
    void messageChanged();

public slots:
private:
    bool m_Paid;
    QString m_TrackingCode;
    QString m_Message;
};

#endif // PAYMENTRESULT_H
