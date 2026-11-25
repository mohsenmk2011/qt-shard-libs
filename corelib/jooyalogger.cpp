#include "jooyalogger.h"

///Refrences
/// https://en.wikipedia.org/wiki/ANSI_escape_code
/// https://misc.flogisoft.com/bash/tip_colors_and_formatting
/// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
/// https://doc.qt.io/qt-5/qtglobal.html#qSetMessagePattern
JooyaLogger::JooyaLogger(QObject *parent) : QObject(parent)
{

    printf("\x1B[31mRed\033[0m");//Red
    printf("\x1B[32mGreen\033[0m");//Green
    printf("\x1B[33mYellow\033[0m");//Yellow
    printf("\x1B[34mBlue\033[0m");//Blue
        printf("\x1B[35mMagenta\033[0m");//Magenta
        printf("\x1B[37mWhite\033[0m");//White
        printf("\x1B[36mCyan\033[0m");//White
        printf("\n");

        printf("\x1B[41;37mRed\033[0m");//Red
        printf("\x1B[42;30mGreen\033[0m");//Green
        printf("\x1B[43;30mYellow\033[0m");//Yellow
        printf("\x1B[44;37mBlue\033[0m");//Blue
        printf("\x1B[45;32mMagenta\033[0m");//Magenta
        printf("\x1B[47;31mWhite\033[0m");//White
        printf("\x1B[46;31mCyan\033[0m");//Cyan
        printf("\n");

    //    printf("\x1B[35;42mTexting\033[0m");//Magenta
    //    printf("\x1B[45;30mTexting\033[0m");//Magenta
    //    printf("\x1B[45;31mTexting\033[0m");//Magenta
    //    printf("\x1B[45;32mTexting\033[0m");//Magenta
    //    printf("\x1B[45;33mTexting\033[0m");//Magenta
    //    printf("\x1B[45;34mTexting\033[0m");//Magenta
    //    printf("\x1B[45;35mTexting\033[0m");//Magenta
    //    printf("\x1B[45;36mTexting\033[0m");//Magenta
    //    printf("\x1B[45;37mTexting\033[0m");//Magenta
    //    printf("\n");

    QString functionColorized=QString("\x1B[47m%{function}\033[0m");
    QString function=QString("%{function}");
    QString lineColorized=QString("\x1B[47;35m%{line}\033[0m");
    QString line=QString("%{line}");
    QString functionLine=QString("[%1(%2)] : ").arg(function).arg(lineColorized);
    QString functionLineColorized=QString("[%1(%2)] : ").arg(functionColorized).arg(lineColorized);

    //=======================
    QString message="%{message}";
    QString redMessage=QString("\x1B[31m%1\033[0m").arg(message);
    QString greenMessage=QString("\x1B[32m%1\033[0m").arg(message);
    QString yellowMessage=QString("\x1B[33m%1\033[0m").arg(message);
    QString blueMessage=QString("\x1B[34m%1\033[0m").arg(message);
    QString magentaMessage=QString("\x1B[35m%1\033[0m").arg(message);
    QString messageColorized=QString("%{if-debug}%1%{endif}%{if-info}%2%{endif}%{if-warning}%3%{endif}%{if-critical}%4%{endif}%{if-fatal}%5%{endif}").arg(blueMessage).arg(greenMessage).arg(yellowMessage).arg(redMessage).arg(magentaMessage);
    //=======================
    //    qSetMessagePattern("[%{function}(%{line})] : %{message}");//Normal
    //    qSetMessagePattern("[\x1B[32m%{function}\033[0m\t(%{line})] : %{message}");//function green
    qSetMessagePattern(QString("%1%2").arg(functionLineColorized).arg(messageColorized));
}
