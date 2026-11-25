#ifndef IMAGEEDITORUTILITY_H
#define IMAGEEDITORUTILITY_H

#include <QObject>
#include<imageoperationtypes.h>
#include<QPointF>
#include<QRectF>
#include<QDebug>
#include<qrect.h>
#include<qrectfextensions.h>

class ImageEditorUtility : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ImageOperationTypes::ImageOperationTypesEnum currentOperation READ currentOperation WRITE setCurrentOperation NOTIFY currentOperationChanged)
    Q_PROPERTY(QPointF dragStartPosition READ dragStartPosition WRITE setDragStartPosition NOTIFY dragStartPositionChanged)
    Q_PROPERTY(QRectF clipRect READ clipRect WRITE setClipRect NOTIFY clipRectChanged)
    Q_PROPERTY(QRectF scaledImageRect READ scaledImageRect WRITE setScaledImageRect NOTIFY scaledImageRectChanged)
    Q_PROPERTY(QPointF currentPosition READ currentPosition WRITE setCurrentPosition NOTIFY currentPositionChanged)

    Q_PROPERTY(QPointF imagePosition READ imagePosition WRITE setImagePosition NOTIFY imagePositionChanged)
    Q_PROPERTY(int cornerDragWidth READ cornerDragWidth WRITE setCornerDragWidth NOTIFY cornerDragWidthChanged FINAL)
    Q_PROPERTY(bool hasFixedClipRect READ hasFixedClipRect WRITE setHasFixedClipRect NOTIFY hasFixedClipRectChanged FINAL)

public:
    explicit ImageEditorUtility(QObject *parent = nullptr);

    /// the current operation that are doing on the image editore page
    const ImageOperationTypes::ImageOperationTypesEnum &currentOperation() const;
    void setCurrentOperation(const ImageOperationTypes::ImageOperationTypesEnum &newCurrentOperation);

    /// the last position that mouse is pressed on the page
    QPointF dragStartPosition() const;
    void setDragStartPosition(QPointF newMousePositionPressed);

    const QRectF &clipRect() const;
    void setClipRect(const QRectF &newClipRect);

    QPointF imagePosition() const;
    void setImagePosition(QPointF newImagePosition);

    QPointF currentPosition() const;
    void setCurrentPosition(QPointF newCurrentPosition);

    const QRectF &scaledImageRect() const;
    void setScaledImageRect(const QRectF &newScaledImageRect);

    int cornerDragWidth() const;
    void setCornerDragWidth(int newCornerDragWidth);

    bool hasFixedClipRect() const;
    void setHasFixedClipRect(bool newHasFixedClipRect);

signals:

    void currentOperationChanged();
    void dragStartPositionChanged();

    void clipRectChanged();

    void imagePositionChanged();

    void currentPositionChanged();

    void scaledImageRectChanged();

    void cornerDragWidthChanged();

    void hasFixedClipRectChanged();

private:
    ImageOperationTypes::ImageOperationTypesEnum m_currentOperation;
    QPointF m_DragStartPosition;
    QRectF m_clipRect;
    void calculateCurrentOperation();
    void doPositionOperation();

    QPointF m_ImagePositionAtDargStart;
    QPointF m_ClipRectPositionAtDragStart;

    QPointF m_imagePosition;
    QPointF m_currentPosition;
    QRectF m_scaledImageRect;
    ///is clip rect is insid scaled image so return
//    bool isValidPosition();
    int m_cornerDragWidth;
    bool m_hasFixedClipRect;
};

#endif // IMAGEEDITORUTILITY_H
