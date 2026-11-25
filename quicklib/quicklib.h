#ifndef QUICKLIB_H
#define QUICKLIB_H

#include<QtQml/QQmlApplicationEngine>
#include<capthaimage.h>
#include<documenthandler.h>
#include<balloon.h>
#include<materialstylehelper.h>
#include<apppagesmanager.h>
#include<imageeditorutility.h>
#include<imageoperationtypes.h>

class Quicklib
{
public:
    Quicklib();
    static void registerTypes()
    {
        qmlRegisterType<DocumentHandler>("Jooya",1,0,"DocumentHandler");
        qmlRegisterType<CapthaImage>("Jooya",1,0,"CapthaImage");
        qmlRegisterType<Balloon>("Jooya",1,0,"Balloon");
        qmlRegisterType<AppPagesManager>("Jooya",1,0,"AppPagesManager");
        qmlRegisterType<ImageEditorUtility>("Jooya",1,0,"ImageEditorUtility");
        qmlRegisterType<ImageOperationTypes>("Jooya",1,0,"ImageOperationTypes");
        qRegisterMetaType<ImageOperationTypes::ImageOperationTypesEnum>("ImageOperationTypes");
    }
};

#endif // QUICKLIB_H
