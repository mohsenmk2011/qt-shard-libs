#ifndef KEYWORDTYPE_H
#define KEYWORDTYPE_H

#include <QObject>
#include<jooyanetwork.h>
#include<QJsonObject>
#include<qjsondocument.h>
#include<QNetworkReply>
#include<keywordlistmodel.h>

class KeywordType : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int keywordTypeId READ keywordTypeId WRITE setKeywordTypeId NOTIFY keywordTypeIdChanged)
    Q_PROPERTY(KeywordListModel* keywords READ keywords CONSTANT)
public:
    explicit KeywordType(QObject *parent = nullptr);    
    KeywordType(int id,QString value);
    KeywordType(QJsonObject obj);

    QString value();
    void setValue(QString v);

    int keywordTypeId();
    void setKeywordTypeId(int ktId);

    void loadFromJson(QJsonObject obj);

    KeywordListModel* keywords();

    Q_INVOKABLE void deleteItem();
    Q_INVOKABLE void save();
    Q_INVOKABLE void addNewKeyword();
signals:
    void keywordTypeIdChanged();
    void valueChanged();
    void deleteSucceed();
    void saveSucceed();
private slots:
    void deleteItemFinished();
    void saveFinished();
private:
    QString m_Value;
    int m_KeywordTypeId;
    KeywordListModel m_Keywords;

    QJsonObject convertToJson();
};

#endif // KEYWORDTYPE_H
