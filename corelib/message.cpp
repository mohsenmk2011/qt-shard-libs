#include "message.h"

Message::Message(QObject *parent) : QObject(parent)
{
    m_BackColor="#4CAF50";
    m_Content="";
    m_Visible=false;
    m_AutoHide=true;
    m_MessageVisibelTime=4500;
    m_Timer=nullptr;
}

QString Message::backColor()
{
    return m_BackColor;
}

void Message::setBackColor(QString bc)
{
    if(bc!=m_BackColor){
        m_BackColor=bc;
        emit backColorChanged();
    }
}

QString Message::content()
{
    return m_Content;
}

void Message::setContent(QString c, bool okMessage)
{
    messageTimerTimeout();
    if(c.isNull()||c.isEmpty()){
        m_Content="پیام ارسال شده تهی است";
    }
    else{
        m_Content=c;
        emit contentChanged();
    }

    if(okMessage){
        setBackColor("#4CAF50");
    }
    else {
        setBackColor("#F44336");
    }
    setVisible(true);
    if(autoHide()){
        if(m_Timer==nullptr){
            m_Timer=new QTimer(this);
            m_Timer->setInterval(m_MessageVisibelTime);
            m_Timer->setParent(this);
            connect(m_Timer,SIGNAL(timeout()),this,SLOT(messageTimerTimeout()));
        }
        m_Timer->start(visibelTime());
    }
}

bool Message::visible()
{
    return m_Visible;
}

void Message::setVisible(bool v)
{
    if(m_Visible!=v){
        m_Visible=v;
        emit visibleChanged(v);
    }
}

bool Message::autoHide()
{
    return m_AutoHide;
}

void Message::setAutoHide(bool ah)
{
    if(m_AutoHide!=ah){
        m_AutoHide=ah;
        emit autoHideChanged();
    }
}

int Message::visibelTime()
{
    return m_MessageVisibelTime;
}

void Message::setVisibelTime(int time)
{
    int t=time*1000;
    if(m_MessageVisibelTime!=t){
        m_MessageVisibelTime=t;
        m_Timer->setInterval(t);
        emit messageVisibelTimeChanged();
    }
}

void Message::messageTimerTimeout(){
    if(m_Timer!=nullptr){
        m_Timer->stop();
    }
    m_Content="";
    setVisible(false);
}
