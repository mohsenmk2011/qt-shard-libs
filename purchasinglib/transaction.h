#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QObject>

class Transaction : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString date READ date WRITE setDate NOTIFY dateChanged)

    Q_PROPERTY(QString resultMessage READ resultMessage WRITE setResultMessage NOTIFY resultMessageChanged)
    Q_PROPERTY(QString shenasehErja READ shenasehErja WRITE setShenasehErja NOTIFY shenasehErjaChanged)
    Q_PROPERTY(QString dargah READ dargah WRITE setDargah NOTIFY dargahChanged)
    Q_PROPERTY(QString creditCardNumber READ creditCardNumber WRITE setCreditCardNumber NOTIFY creditCardNumberChanged)

public:
    explicit Transaction(QObject *parent = nullptr);
    Transaction(QString id, QString date, QString resultMessage, QString shenasehErja, QString dargah, QString creditCardNumber);
    QString id();
    void setId(QString i);

    QString date();
    void setDate(QString d);

    QString resultMessage();
    void setResultMessage(QString r);

    QString shenasehErja();
    void setShenasehErja(QString s);

    QString dargah();
    void setDargah(QString d);

    QString creditCardNumber();
    void setCreditCardNumber(QString c);


signals:
    void idChanged();
    void dateChanged();
    void resultMessageChanged();
    void shenasehErjaChanged();
    void dargahChanged();
    void creditCardNumberChanged();
public slots:
private:
    QString m_Id;
    QString m_Date;
    QString m_ResultMessage;
    QString m_ShenasehErja;
    QString m_Dargah;
    QString m_CreditCardNumber;
};

#endif // TRANSACTION_H
