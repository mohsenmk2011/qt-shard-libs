#include "documentelement.h"

DocumentElement::DocumentElement(QObject *parent) : JavaScriptGenerator(parent)
{    
    m_CurrentJavaScript = "document.documentElement";
}

QString DocumentElement::value()
{
    m_CurrentJavaScript+=QString(".value");
    return m_CurrentJavaScript;
}

void DocumentElement::setValue(QString value)
{
    m_CurrentJavaScript+=QString(".value = '%2'").arg(value);
}
