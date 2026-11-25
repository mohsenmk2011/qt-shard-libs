#include "documenthandler.h"

DocumentHandler::DocumentHandler(QObject *parent) : QObject(parent)
  , m_document(nullptr)
  , m_cursorPosition(-1)
  , m_selectionStart(0)
  , m_selectionEnd(0)
{
    m_fontSize=17;
    m_fileUrl=QUrl();
}

QQuickTextDocument *DocumentHandler::document() const
{
    return m_document;
}

void DocumentHandler::setDocument(QQuickTextDocument *document)
{
    if (document == m_document)
        return;

    m_document = document;
    emit documentChanged();
}

int DocumentHandler::cursorPosition() const
{
    return m_cursorPosition;
}

void DocumentHandler::setCursorPosition(int position)
{
    if (position == m_cursorPosition)
        return;

    m_cursorPosition = position;
    qDebug()<<" DocumentHandler::setCursorPosition=>"<<position;
    textCursor().setPosition(position);
    reset();
    emit cursorPositionChanged();
}

int DocumentHandler::selectionStart() const
{
    return m_selectionStart;
}

void DocumentHandler::setSelectionStart(int position)
{
    if (position == m_selectionStart)
        return;

    m_selectionStart = position;
    emit selectionStartChanged();
}

int DocumentHandler::selectionEnd() const
{
    return m_selectionEnd;
}

void DocumentHandler::setSelectionEnd(int position)
{
    if (position == m_selectionEnd)
        return;

    m_selectionEnd = position;
    emit selectionEndChanged();
}

QString DocumentHandler::fontFamily() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return QString();
    QTextCharFormat format = cursor.charFormat();
    return format.font().family();
}

void DocumentHandler::setFontFamily(const QString &family)
{
    QTextCharFormat format;
    format.setFontFamily(family);
    mergeFormatOnWordOrSelection(format);
    emit fontFamilyChanged();
}

QColor DocumentHandler::textColor() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return QColor(Qt::black);
    QTextCharFormat format = cursor.charFormat();
    return format.foreground().color();
}

void DocumentHandler::setTextColor(const QColor &color)
{
    QTextCharFormat format;
    format.setForeground(QBrush(color));
    mergeFormatOnWordOrSelection(format);
    emit textColorChanged();
}

Qt::Alignment DocumentHandler::alignment() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return Qt::AlignLeft;
    return textCursor().blockFormat().alignment();
}

void DocumentHandler::setAlignment(Qt::Alignment alignment)
{
    qDebug()<<"alignment=> "<<alignment;
    QTextBlockFormat format;
    QTextCursor cursor = textCursor();
    if(alignment==Qt::AlignRight)
    {
        format.setLayoutDirection(Qt::RightToLeft);
        format.setAlignment(Qt::AlignLeft);
        //cursor.blockFormat().setLayoutDirection(Qt::RightToLeft);
    }
    else if(alignment==Qt::AlignLeft)
    {
        format.setLayoutDirection(Qt::LeftToRight);
        format.setAlignment(Qt::AlignLeft);

        //cursor.blockFormat().setLayoutDirection(Qt::LeftToRight);
    }
    else if(alignment==Qt::AlignHCenter)
    {
        format.setAlignment(alignment);
        qDebug()<<"align to center"<<alignment;
    }
    cursor.mergeBlockFormat(format);
    //cursor.blockFormat().setAlignment(alignment);


    // Determine the current text direction
    Qt::LayoutDirection dir = cursor.block().textDirection();
    if(dir==Qt::RightToLeft)
    {
        //to update the anchor of cursor
        //temporary insert a char(e) at the end and then selected it and delete it
        cursor.insertText(" ");
        cursor.movePosition(QTextCursor::End);
        cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,1);
        cursor.deleteChar();
    }
    else{
        //to update the anchor of cursor
        //temporary insert a char(e) at the end and then selected it and delete it
        cursor.insertText(" ");
        cursor.movePosition(QTextCursor::End);
        cursor.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,1);
        cursor.deleteChar();
    }
    //=================================

       //Qt::LayoutDirection dir = cursor.block().text().blockFormat().setLayoutDirection();
    //to update the anchor of cursor
    //temporary insert a char(e) at the end and then selected it and delete it
//    cursor.insertText("Me4SW2");
//    cursor.movePosition(QTextCursor::End);
//    cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,6);
//    if(cursor.selectedText()!="Me4SW2"){
//        cursor.movePosition(QTextCursor::End);
//        cursor.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,6);
//    }
//    cursor.deleteChar();
    emit alignmentChanged();
}

bool DocumentHandler::bold() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return cursor.charFormat().fontWeight() == QFont::Bold;
}

void DocumentHandler::setBold(bool bold)
{
    QTextCharFormat format;
    format.setFontWeight(bold ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(format);
    emit boldChanged();
}

bool DocumentHandler::italic() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontItalic();
}

void DocumentHandler::setItalic(bool italic)
{
    QTextCharFormat format;
    format.setFontItalic(italic);
    mergeFormatOnWordOrSelection(format);
    emit italicChanged();
}

bool DocumentHandler::underline() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return false;
    return textCursor().charFormat().fontUnderline();
}

void DocumentHandler::setUnderline(bool underline)
{
    QTextCharFormat format;
    format.setFontUnderline(underline);
    mergeFormatOnWordOrSelection(format);
    emit underlineChanged();
}

int DocumentHandler::fontSize() const
{
    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return 0;
    QTextCharFormat format = cursor.charFormat();
    return format.font().pointSize();
}

void DocumentHandler::setFontSize(int size)
{
    if (size <= 0)
        return;

    QTextCursor cursor = textCursor();
    if (cursor.isNull())
        return;

    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);

    if (cursor.charFormat().property(QTextFormat::FontPointSize).toInt() == size)
        return;

    QTextCharFormat format;
    format.setFontPointSize(size);
    mergeFormatOnWordOrSelection(format);
    emit fontSizeChanged();
}

QString DocumentHandler::fileName() const
{
    const QString filePath = QQmlFile::urlToLocalFileOrQrc(m_fileUrl);
    const QString fileName = QFileInfo(filePath).fileName();
    if (fileName.isEmpty())
        return QStringLiteral("untitled.txt");
    return fileName;
}

QString DocumentHandler::fileType() const
{
    return QFileInfo(fileName()).suffix();
}

QUrl DocumentHandler::fileUrl() const
{
    return m_fileUrl;
}

// void DocumentHandler::load(const QUrl &fileUrl)
// {
//     if (fileUrl == m_fileUrl)
//         return;

//     QQmlEngine *engine = qmlEngine(this);
//     if (!engine) {
//         qWarning() << "load() called before DocumentHandler has QQmlEngine";
//         return;
//     }

//     const QUrl path = QQmlFileSelector::get(engine)->selector()->select(fileUrl);
//     const QString fileName = QQmlFile::urlToLocalFileOrQrc(path);
//     if (QFile::exists(fileName)) {
//         QFile file(fileName);
//         if (file.open(QFile::ReadOnly)) {
//             QByteArray data = file.readAll();
//             QTextCodec *codec = QTextCodec::codecForHtml(data);
//             if (QTextDocument *doc = textDocument())
//                 doc->setModified(false);

//             emit loaded(codec->toUnicode(data));
//             reset();
//         }
//     }

//     m_fileUrl = fileUrl;
//     emit fileUrlChanged();
// }

void DocumentHandler::saveAs(const QUrl &fileUrl)
{
    QTextDocument *doc = textDocument();
    if (!doc)
        return;

    const QString filePath = fileUrl.toLocalFile();
    const bool isHtml = QFileInfo(filePath).suffix().contains(QLatin1String("htm"));
    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Truncate | (isHtml ? QFile::NotOpen : QFile::Text))) {
        emit error(tr("Cannot save: ") + file.errorString());
        return;
    }
    file.write((isHtml ? doc->toHtml() : doc->toPlainText()).toUtf8());
    file.close();

    if (fileUrl == m_fileUrl)
        return;

    m_fileUrl = fileUrl;
    emit fileUrlChanged();
}

void DocumentHandler::reset()
{
    emit fontFamilyChanged();
    emit alignmentChanged();
    emit boldChanged();
    emit italicChanged();
    emit underlineChanged();
    emit fontSizeChanged();
    emit textColorChanged();
}

QTextCursor DocumentHandler::textCursor() const
{
    QTextDocument *doc = textDocument();
    if (!doc)
        return QTextCursor();

    QTextCursor cursor = QTextCursor(doc);
    if (m_selectionStart != m_selectionEnd) {
        cursor.setPosition(m_selectionStart);
        cursor.setPosition(m_selectionEnd, QTextCursor::KeepAnchor);
    } else {
        cursor.setPosition(m_cursorPosition);
    }
    return cursor;
}
void DocumentHandler::insertImage(QImage img){
    //        textCursor().insertImage(img);
    //    textCursor().movePosition()
    textDocument()->addResource(QTextDocument::ImageResource,QUrl("mydata://image.png"),QVariant(img));
    QTextImageFormat imageFormat;
    imageFormat.setHeight(img.height());
    imageFormat.setWidth(img.width());
    imageFormat.setName("mydata://image.png");
    textCursor().insertImage(imageFormat);

}

void DocumentHandler::insertImage(QString source){
    //    textCursor().insertImage(img);
    //    QTextImageFormat imgFormat;
    //    imgFormat.setHeight(img.height());
    //    imgFormat.setWidth(img.width());
    //    imgFormat.set
    //    textCursor().movePosition()

    //for fix this bug:when user goes new line and he want to insert an image with center alignment,
    //becuase there is not char before the image ,so when new image will be inserted,
    //it will loose it's alignment for example it will be insert with right or left alignment
    //fo fix that: it will insert new space beofre the insertion of image
    QTextCursor cursor = textCursor();
    qDebug()<<"cursorPosition=" <<cursorPosition();
    textCursor().insertHtml(HtmlHelper ::getImgTag(source));
    qDebug()<<"cursorPosition=" <<cursorPosition();
}

QTextDocument *DocumentHandler::textDocument() const
{
    if (!m_document)
        return nullptr;

    return m_document->textDocument();
}

void DocumentHandler::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
}
