#include "object.h"

bool Object::Accelerate(const int& dX, const int& dY){
    xSpeed = dX;
    ySpeed = dY;
    return TRUE;
}
