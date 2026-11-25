#include "javascriptgenerator.h"

JavaScriptGenerator::JavaScriptGenerator(QObject *parent) : QObject(parent)
{
    m_CurrentJavaScript="";
}

QString JavaScriptGenerator::isNull()
{
    m_CurrentJavaScript+= "==null";
    return m_CurrentJavaScript;
}

QString JavaScriptGenerator::click()
{
    m_CurrentJavaScript+= ".click()";
    return m_CurrentJavaScript;
}

QString JavaScriptGenerator::convertToString()
{
    return m_CurrentJavaScript;
}

QString JavaScriptGenerator::outerHTML()
{
    m_CurrentJavaScript+=".outerHTML";
    return m_CurrentJavaScript;
}

QString JavaScriptGenerator::innerHTML()
{
    m_CurrentJavaScript+=".innerHTML";
    return m_CurrentJavaScript;
}
