#ifndef KEYWORD_H
#define KEYWORD_H

#include <QObject>
#include<jooyanetwork.h>
#include<QJsonObject>

class Keyword : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(int keywordId READ keywordId WRITE setKeywordId NOTIFY keywordIdChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
    Q_PROPERTY(int parentId READ parentId WRITE setParentId NOTIFY parentIdChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit Keyword(QObject *parent = nullptr);
    Keyword(int ktId);
    Keyword(QJsonObject json);
    void loadFromJson(QJsonObject json);

    int keywordId();
    void setKeywordId(int kId);

    int parentId();
    void setParentId(int ktId);

    QString value();
    void setValue(QString v);

    bool selected();
    void setSelected(bool s);

    Q_INVOKABLE void save();
    Q_INVOKABLE void deleteItem();
signals:
    void keywordIdChanged();
    void parentIdChanged();
    void valueChanged();
    void selectedChanged();

    void saveSucceed();
    void deleteSucceed();
private slots:
    void saveFinished();
    void deleteItemFinished();
private:
    int m_KeywordId;
    int m_ParentId;
    QString m_Value;
    bool m_Selected;
    QJsonObject convertToJson();
    bool isFeildsValid();
};

#endif // KEYWORD_H
