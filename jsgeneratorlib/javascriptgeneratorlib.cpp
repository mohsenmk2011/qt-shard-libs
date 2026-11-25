#include "javascriptgeneratorlib.h"

JavaScriptGeneratorLib::JavaScriptGeneratorLib()
{
}

void JavaScriptGeneratorLib::registerTypes()
{
    qmlRegisterType<JavaScriptGenerator>("Jooya",1,0,"JavaScriptGenerator");
    qmlRegisterType<JavaScriptDocument>("Jooya",1,0,"JavaScriptDocument");
    qmlRegisterType<DocumentElement>("Jooya",1,0,"DocumentElement");
}
