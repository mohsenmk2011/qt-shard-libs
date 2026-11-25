#include "javascriptdocument.h"

JavaScriptDocument::JavaScriptDocument(QObject *parent) : JavaScriptGenerator(parent)
{
    m_CurrentJavaScript="document";
}

DocumentElement *JavaScriptDocument::documentElement()
{
    return new DocumentElement();
}

DocumentElement *JavaScriptDocument::getElementById(QString id)
{
    DocumentElement* de=new DocumentElement();
    de->m_CurrentJavaScript=m_CurrentJavaScript+QString(".getElementById('%1')").arg(id);
    return de;
}

DocumentElement *JavaScriptDocument::getElementsByTagName(QString name)
{
    DocumentElement* de=new DocumentElement();
    de->m_CurrentJavaScript=m_CurrentJavaScript+QString(".getElementsByTagName('%1')").arg(name);
    return de;
}

DocumentElement *JavaScriptDocument::getElementsByClassName(QString name)
{
    DocumentElement* de=new DocumentElement();
    de->m_CurrentJavaScript=m_CurrentJavaScript+QString(".getElementsByClassName('%1')[0]").arg(name);
    return de;
}

void JavaScriptDocument::appendScript(QString script)
{
    m_Scripts.append(script);
}

QString JavaScriptDocument::script()
{
    QString s="";
    for (int i = 0; i < m_Scripts.count(); ++i) {
        s+=m_Scripts.at(i)+";";
    }
    return s;
}
