#ifndef USERIMAGE_H
#define USERIMAGE_H

#include <QObject>
#include<file.h>
#include<applicationpath.h>
#include<QDebug>
#include<imagefile.h>
#include<datetimeutility.h>

class UserImage : public ImageFile
{
    Q_OBJECT
    Q_PROPERTY(QDateTime date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QString persianDate READ persianDate WRITE setPersianDate NOTIFY persianDateChanged)
    Q_PROPERTY(bool isDefault READ isDefault CONSTANT)

public:
    explicit UserImage(QObject *parent = nullptr);
    UserImage(int id, QDateTime date, QString url);
    UserImage(QJsonObject jobj);

    QDateTime date();
    void setDate(QDateTime d);

    QString persianDate();
    void setPersianDate(QString d);

    Q_INVOKABLE void deleteItem();

    bool isDefault();

    void loadFromJson(QJsonObject obj);
    QJsonObject toJson() override;
    Q_INVOKABLE void resetImage();
signals:
    void dateChanged();
    void deleted();
    void persianDateChanged();

private slots:
    void deleteItemFinished();
private:
    QDateTime m_Date;
    QString m_PersianDate;
};

#endif // USERIMAGE_H
