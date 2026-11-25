#ifndef JOOYANETWORKENGINE_H
#define JOOYANETWORKENGINE_H

#include <QObject>
#include<QDebug>
#include<QTimer>
#include<message.h>
#include<QQmlEngine>
#include<userlogininfo.h>
#include<QJsonObject>
#include<operationtypes.h>
#include<filewatcher.h>
#include<jsonutility.h>
#include<datetimeutility.h>

class JooyaNetworkEngine : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Message* message READ message CONSTANT)
    Q_PROPERTY(bool isProcessing READ isProcessing WRITE setIsProcssing NOTIFY isProcessingChanged)
    Q_PROPERTY(QString operationMessage READ operationMessage WRITE setOperationMessage NOTIFY operationMessageChanged)

    Q_PROPERTY(UserLoginInfo* loginInfo READ loginInfo CONSTANT)
    Q_PROPERTY(OperationTypes::OperationTypesEnum operationType READ operationType WRITE setOperationType NOTIFY operationTypeChanged)
public:
    explicit JooyaNetworkEngine(QObject *parent = nullptr);

    virtual QJsonObject toJson();
    virtual void fromJson(QJsonObject json);

    Message* message();
//    void setMessage(Message* m);
    static Message* m_Message;

    JsonUtility *jsonUtility();
    DateTimeUtility *dateTimeUtility();

    UserLoginInfo* loginInfo();
    static UserLoginInfo* m_loginInfo;
    static FileWatcher* m_FileWather;

    static bool isNetworkIsAccessible;

    bool isProcessing();
    void setIsProcssing(bool isProcessing);

    bool displayCommonErrorMessage();
    void setDisplayCommonErrorMessage(bool show);

    QString operationMessage();
    void setOperationMessage(QString message);

    OperationTypes::OperationTypesEnum operationType();
    void setOperationType(OperationTypes::OperationTypesEnum o);

    QString baseUrl();
    void setBaseUrl(QString url);

    QString apiUrl();
    void setApiUrl(QString url);

signals:    
//    void messageChanged();
    void isProcessingChanged(bool isProcessing);
    void operationMessageChanged();
    void operationTypeChanged();
public slots:
private:
    static QString m_BaseUrl;
    static QString m_ApiUrl;
    bool m_IsProccessing;
    bool m_DisplayCommonErrorMessage;
    QString m_OperationMessage;
    OperationTypes::OperationTypesEnum m_OperationType;
};

#endif // JOOYANETWORKENGINE_H

