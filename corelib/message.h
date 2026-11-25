#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include<QTimer>
#include<QDebug>
#include<QQmlEngine>

class Message : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(QString backColor READ backColor WRITE setBackColor NOTIFY backColorChanged)
    Q_PROPERTY(QString content READ content WRITE setContent NOTIFY contentChanged)
    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(bool autoHide READ autoHide WRITE setAutoHide NOTIFY autoHideChanged)
    Q_PROPERTY(int visibelTime READ visibelTime WRITE setVisibelTime NOTIFY messageVisibelTimeChanged)

public:
    explicit Message(QObject *parent = nullptr);

    QString backColor();
    void setBackColor(QString bc);

    QString content();
    Q_INVOKABLE void setContent(QString c, bool okMessage=false);

    bool visible();
    void setVisible(bool v);

    bool autoHide();
    void setAutoHide(bool ah);

    int visibelTime();
    void setVisibelTime(int time);

signals:
    void backColorChanged();
    void contentChanged();
    void visibleChanged(bool isVisible);
    void messageTypeChanged();
    void preferedButtonChanged();
    void autoHideChanged();
    void messageVisibelTimeChanged();
public slots:
    void messageTimerTimeout();
private:
    QTimer* m_Timer;
    QString m_BackColor;
    QString m_Content;
    bool m_Visible;
    bool m_AutoHide;
    int m_MessageVisibelTime;
};

#endif // MESSAGE_H
