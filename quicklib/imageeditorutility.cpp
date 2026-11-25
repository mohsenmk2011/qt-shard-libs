#include "imageeditorutility.h"

ImageEditorUtility::ImageEditorUtility(QObject *parent)
    : QObject{parent}
{
    m_cornerDragWidth = 18;
    m_hasFixedClipRect = true;
}

const ImageOperationTypes::ImageOperationTypesEnum &ImageEditorUtility::currentOperation() const
{
    return m_currentOperation;
}

void ImageEditorUtility::setCurrentOperation(const ImageOperationTypes::ImageOperationTypesEnum &newCurrentOperation)
{
    if (m_currentOperation == newCurrentOperation)
        return;
    m_currentOperation = newCurrentOperation;
    emit currentOperationChanged();
}

QPointF ImageEditorUtility::dragStartPosition() const
{
    return m_DragStartPosition;
}

void ImageEditorUtility::setDragStartPosition(QPointF newMousePositionPressed)
{
    if (m_DragStartPosition == newMousePositionPressed)
        return;
    qDebug()<<"mouse pressed";
    m_DragStartPosition = newMousePositionPressed;
    m_ImagePositionAtDargStart =imagePosition();//scaledImageRect().topLeft();///
    m_ClipRectPositionAtDragStart = clipRect().topLeft();
    calculateCurrentOperation();
    emit dragStartPositionChanged();
}

const QRectF &ImageEditorUtility::clipRect() const
{
    return m_clipRect;
}

void ImageEditorUtility::setClipRect(const QRectF &newClipRect)
{
    if (m_clipRect == newClipRect)
        return;
    m_clipRect = newClipRect;
    emit clipRectChanged();
}

void ImageEditorUtility::calculateCurrentOperation()
{
    qDebug()<<"is going to calculate current image operation";
    // becuase the mouse area is filled the whole page,so the mouse positon is based of x,y of the page
    // if your want to get postion of of mouse base on the clip rect so
    //QPointF clipRectMousePosition = QPointF(dragStartPosition().x()+clipRect().x(),dragStartPosition().y()+clipRect().y());
    // is mouse pressed inside the rect clip?
    //bool isInsideClipRect = clipRect().contains(clipRectMousePosition);
    if(!hasFixedClipRect())
    {
        //--------------------------< if mouse pressed at corners >------------------------------
        QRectF topLeft = QRectFExtensions::topLeft(clipRect(),cornerDragWidth(),cornerDragWidth());
        if(topLeft.contains(dragStartPosition())){
            qDebug()<<"inside top left clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromTopLeft);
            return;
        }
        QRectF topRight = QRectFExtensions::topRight(clipRect(),cornerDragWidth(),cornerDragWidth());
        if(topRight.contains(dragStartPosition())){
            qDebug()<<"inside top right clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromTopRight);
            return;
        }
        QRectF bottomLeft = QRectFExtensions::bottomLeft(clipRect(),cornerDragWidth(),cornerDragWidth());
        if(bottomLeft.contains(dragStartPosition())){
            qDebug()<<"inside bottom left clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromBottomLeft);
            return;
        }
        QRectF bottomRight = QRectFExtensions::bottomRight(clipRect(),cornerDragWidth(),cornerDragWidth());
        if(bottomRight.contains(dragStartPosition())){
            qDebug()<<"inside bottom right clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromBottomRight);
            return;
        }
        //--------------------------< if mouse pressed at borders >------------------------------
        QRectF left = QRectFExtensions::left(clipRect(),cornerDragWidth());
        if(left.contains(dragStartPosition())){
            qDebug()<<"inside left clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromLeft);
            return;
        }
        QRectF right = QRectFExtensions::right(clipRect(),cornerDragWidth());
        qDebug()<<"inside right  clip rect";
        if(right.contains(dragStartPosition())){
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromRight);
            return;
        }
        QRectF top = QRectFExtensions::top(clipRect(),cornerDragWidth());
        if(top.contains(dragStartPosition())){
            qDebug()<<"inside top clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromTop);
            return;
        }
        QRectF bottom = QRectFExtensions::bottom(clipRect(),cornerDragWidth());
        if(bottom.contains(dragStartPosition())){
            qDebug()<<"inside bottom clip rect";
            setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ResizeFromBottom);
            return;
        }
    }
    //--------------------------< if mouse pressed at inside rect cip >------------------------------

    qDebug()<<"inside image";
    setCurrentOperation(ImageOperationTypes::ImageOperationTypesEnum::ImagePosition);


}

void ImageEditorUtility::doPositionOperation()
{
    //QPointF delta = QPointF(currentPosition().x()-dragStartPosition().x(),currentPosition().y()-dragStartPosition().y());
    QPointF delta = QPointF(currentPosition().x()-dragStartPosition().x(),currentPosition().y()-dragStartPosition().y());
    qDebug()<<"delta => "<<delta;
    //---------------------------< resize clip rect from corners >---------------------------
    if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromTopLeft){
        qDebug()<<"resize clip rect from top left";
        QPointF newPosition = QPointF(clipRect().right()+delta.x(),clipRect().bottom()+delta.y());
        QRectF newClipRect = clipRect();// QRectF(newPosition.x(),newPosition.y(),clipRect().width(),clipRect().height());
       newClipRect.moveBottomRight(newPosition);
        newClipRect.setSize(QSizeF(clipRect().width()-delta.x(),clipRect().height()-delta.y()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromBottomRight){
        qDebug()<<"resize clip rect from bottom right";
        QPointF newPosition = QPointF(clipRect().left()-delta.x(),clipRect().top()-delta.y());
        QRectF newClipRect = clipRect();// QRectF(newPosition.x(),newPosition.y(),clipRect().width(),clipRect().height());
        //newClipRect.moveTopLeft(newPosition);
        newClipRect.setSize(QSizeF(clipRect().width()+delta.x(),clipRect().height()+delta.y()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromBottomLeft){
        qDebug()<<"resize clip rect from bottom left";
        QPointF newPosition = QPointF(clipRect().right()+delta.x(),clipRect().top());
        QRectF newClipRect = clipRect();// QRectF(newPosition.x(),newPosition.y(),clipRect().width(),clipRect().height());
        newClipRect.moveTopRight(newPosition);
        newClipRect.setSize(QSizeF(clipRect().width()-delta.x(),clipRect().height()+delta.y()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromTopRight){
        qDebug()<<"resize clip rect from top right";
        QPointF newPosition = QPointF(clipRect().left(),clipRect().bottom()+delta.y());
        QRectF newClipRect = clipRect();// QRectF(newPosition.x(),newPosition.y(),clipRect().width(),clipRect().height());
        newClipRect.moveBottomLeft(newPosition);
        newClipRect.setSize(QSizeF(clipRect().width()+delta.x(),clipRect().height()-delta.y()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    //---------------------------< resize clip rect from borders >---------------------------
    if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromTop){
        qDebug()<<"resize clip rect from top";
        qreal newY =clipRect().bottom()+delta.y();
        QRectF newClipRect = clipRect();
        newClipRect.moveBottom(newY);
        newClipRect.setSize(QSizeF(clipRect().width(),clipRect().height()-delta.y()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromBottom){
        qDebug()<<"resize clip rect from bottom";
        QRectF newClipRect = clipRect();
        newClipRect.setSize(QSizeF(clipRect().width(),clipRect().height()+delta.y()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromLeft){
        qDebug()<<"resize clip rect from left";
        qreal newX = clipRect().right()+delta.x();
        QRectF newClipRect = clipRect();
        newClipRect.moveRight(newX);
        newClipRect.setSize(QSizeF(clipRect().width()-delta.x(),clipRect().height()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ResizeFromRight){
        qDebug()<<"resize clip rect from right";
        QRectF newClipRect = clipRect();
        newClipRect.setSize(QSizeF(clipRect().width()+delta.x(),clipRect().height()));
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    //------------------------------< move clip rect position >------------------------------
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ClipRectPosition){
        qDebug()<<"change Clip Rect position";
        QPointF newPosition = QPointF(clipRect().x()+delta.x(),clipRect().y()+delta.y());
        QRectF newClipRect = clipRect();// QRectF(newPosition.x(),newPosition.y(),clipRect().width(),clipRect().height());
        newClipRect.moveTopLeft(newPosition);
        if(scaledImageRect().contains(newClipRect)){
            setClipRect(newClipRect);
        }
    }
    //--------------------------------< move image position >---------------------------------
    else if(currentOperation()==ImageOperationTypes::ImageOperationTypesEnum::ImagePosition){

        qDebug()<<"change image position";
        //QPointF newPosition = QPointF(m_ImagePositionAtDargStart.x()+delta.x(),m_ImagePositionAtDargStart.y()+delta.y());
        QPointF newPosition = QPointF(scaledImageRect().x()+delta.x(),scaledImageRect().y()+delta.y());
        qDebug()<<"newPosition=> "<<newPosition;
        QRectF newImageRect=scaledImageRect();
        qDebug()<<"scaledImageRect => "<<scaledImageRect();
        newImageRect.moveTopLeft(newPosition);
        qDebug()<<"newImageRect => "<<newImageRect;
        if(newImageRect.contains(clipRect())){
            setScaledImageRect(newImageRect);
        }
    }
    setDragStartPosition(currentPosition());
}

//bool ImageEditor::isValidPosition()
//{
//    return scaledImageRect().contains(clipRect())
//    console.info("clip rect is going to protrude from scaled image so return");
//    return true;
//}

QPointF ImageEditorUtility::imagePosition() const
{
    return m_imagePosition;
}

void ImageEditorUtility::setImagePosition(QPointF newImagePosition)
{
    if (m_imagePosition == newImagePosition)
        return;
    m_imagePosition = newImagePosition;
    emit imagePositionChanged();
}

QPointF ImageEditorUtility::currentPosition() const
{
    return m_currentPosition;
}

void ImageEditorUtility::setCurrentPosition(QPointF newCurrentPosition)
{
    if (m_currentPosition == newCurrentPosition)
        return;
    m_currentPosition = newCurrentPosition;
    doPositionOperation();
    emit currentPositionChanged();
}

const QRectF &ImageEditorUtility::scaledImageRect() const
{
    return m_scaledImageRect;
}

void ImageEditorUtility::setScaledImageRect(const QRectF &newScaledImageRect)
{
    if (m_scaledImageRect == newScaledImageRect)
        return;
    m_scaledImageRect = newScaledImageRect;
    emit scaledImageRectChanged();
}

int ImageEditorUtility::cornerDragWidth() const
{
    return m_cornerDragWidth;
}

void ImageEditorUtility::setCornerDragWidth(int newCornerDragWidth)
{
    if (m_cornerDragWidth == newCornerDragWidth)
        return;
    m_cornerDragWidth = newCornerDragWidth;
    emit cornerDragWidthChanged();
}

bool ImageEditorUtility::hasFixedClipRect() const
{
    return m_hasFixedClipRect;
}

void ImageEditorUtility::setHasFixedClipRect(bool newHasFixedClipRect)
{
    if (m_hasFixedClipRect == newHasFixedClipRect)
        return;
    m_hasFixedClipRect = newHasFixedClipRect;
    emit hasFixedClipRectChanged();
}
