#ifndef IMAGEOPERATIONTYPES_H
#define IMAGEOPERATIONTYPES_H

#include <QObject>

class ImageOperationTypes : public QObject
{
    Q_OBJECT
public:
    enum class ImageOperationTypesEnum:unsigned int{
        Unknown = 0,
        ImagePosition = 1,
        ClipRectPosition = 2,
        ResizeFromTopLeft = 3,
        ResizeFromTopRight = 4,
        ResizeFromBottomLeft = 5,
        ResizeFromBottomRight = 6,
        ResizeFromTop = 7,
        ResizeFromRight = 8,
        ResizeFromBottom = 9,
        ResizeFromLeft = 10,
    };
    Q_ENUM(ImageOperationTypesEnum)

};

#endif // IMAGEOPERATIONTYPES_H
