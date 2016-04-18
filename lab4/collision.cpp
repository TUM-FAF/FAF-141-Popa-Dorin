#include "object.h"

bool Object::Collision(const RECT &rect){
    if(center.x+25 > rect.right-1)
    {
        xSpeed =- abs(xSpeed);
        counter=1;
    }
    if(center.x-25 < rect.left+1)
    {
        xSpeed = abs(xSpeed);
        counter=1;
    }
    if(center.y+25 > rect.bottom-1)
    {
        ySpeed = -abs(ySpeed);
    }
    if(center.y-25 < rect.top+1)
    {
        ySpeed = +abs(ySpeed);
    }
    return TRUE;
}


