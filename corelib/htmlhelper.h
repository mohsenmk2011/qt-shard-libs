#ifndef HTMLHELPER_H
#define HTMLHELPER_H

#include <QObject>
#include <QRegularExpression>

class HtmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit HtmlHelper(QObject *parent = nullptr);

    static QString removePStyle(const QString &html)
    {
        QRegularExpression regex("<p([^>]*) style=\"([^\"]*)\"([^>]*)>", QRegularExpression::CaseInsensitiveOption);
        QString result = html;
        result.replace(regex, "<p\\1\\3>");
        return result;
    }
    static QString removeP_Br_NewLines(const QString &html)
    {
        // Regular expression to match <p>, <br />, and \n
        QRegularExpression regex("<[pP][^>]*>|</[pP]>|<br\\s*/>|\\n");
        QString result = html;

        // Replace matches with an empty string
        return result.replace(regex, "");
    }

    static QString extractBodyHtml(const QString &html)
    {
        QRegularExpression regex("<body[^>]*>([\\s\\S]*?)<\\/body>", QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = regex.match(html);
        if (match.hasMatch()) {
            return match.captured(1);
        } else {
            return "";
        }
    }
    static QString getImgTag(QString source)
    {
        return QString("<img src=\"%1\" />").arg(source);
    }
    static QString replaceImageSource(QString html, QString oldSrc, QString newSrc)
    {
        QRegularExpression rx("<img\\b[^>]*\\bsrc=['\"]" + QRegularExpression::escape(oldSrc) + "['\"][^>]*>");
        QRegularExpressionMatch match;
        int pos = 0;

        while ((pos = html.indexOf(rx, pos, &match)) != -1) {
            QString oldTag = match.captured(0);
            QString newTag = oldTag.replace(oldSrc, newSrc);
            html.replace(pos, match.capturedLength(0), newTag);
            pos += newTag.length();
        }
        return html;
    }
signals:

};

#endif // HTMLHELPER_H
