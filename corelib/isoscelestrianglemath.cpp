#include "isoscelestrianglemath.h"

IsoscelesTriangleMath::IsoscelesTriangleMath(QObject *parent)
    : QObject{parent}
{

}
// Function to calculate the side length of an isosceles triangle
// Input: chord - the length of the chord
//        angle - the angle between the sides and the base
// Output: the length of the side
qreal IsoscelesTriangleMath::calculateSideLength(qreal chord, qreal angle) {
    // Calculate the side length using trigonometric functions
    qreal side = 2 * chord * qSin(qDegreesToRadians(angle / 2));
    return side;
}
