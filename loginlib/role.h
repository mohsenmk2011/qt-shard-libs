#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include<jooyanetwork.h>

class Role : public JooyaNetwork
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(bool selected READ selected WRITE setSelected NOTIFY selectedChanged)
public:
    explicit Role(QObject *parent = nullptr);
    Role(QString name,QString id,bool selected=false);

    QString id();
    void setId(QString id);

    QString name();
    void setName(QString id);

    bool selected();
    void setSelected(bool id);

    Q_INVOKABLE void save();
    Q_INVOKABLE void deleteRole();

signals:
    void idChanged();
    void nameChanged();
    void selectedChanged();
    void deleted();
public slots:
    void saveFinished();
    void deleteRoleFinished();
private:
    QString m_Id;
    QString m_Name;
    bool m_Selected;
};

#endif // ROLE_H
