#include "object.h"

bool Interaction(Object &obj1, Object &obj2) {

    float d;

    d = sqrt( pow(obj1.center.x-obj2.center.x,2) + pow(obj1.center.y-obj2.center.y,2) );

    if ( d < 55 )
    {
    obj1.Accelerate(-obj1.xSpeed, -obj1.ySpeed);
    obj2.Accelerate(-obj2.xSpeed, -obj2.ySpeed);

    obj1.Color(RGB(255,255,0));
    }

    return TRUE;
}
