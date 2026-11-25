#ifndef KEYWORDTYPEMANAGER_H
#define KEYWORDTYPEMANAGER_H

#include <QObject>
#include<jooyanetwork.h>
#include<keywordtypelistmodel.h>

class KeywordTypeManager : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(KeywordTypeListModel* listModel READ listModel CONSTANT)
public:
    explicit KeywordTypeManager(QObject *parent = nullptr);

    Q_INVOKABLE void getList();
    KeywordTypeListModel* listModel();
    Q_INVOKABLE void addNewItem();

signals:

private slots:
    void getListFinished();
private:
    KeywordTypeListModel m_ListModel;
};

#endif // KEYWORDTYPEMANAGER_H
