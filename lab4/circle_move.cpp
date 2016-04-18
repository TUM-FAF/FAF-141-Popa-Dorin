#include "object.h"

bool Circle::Move(const HDC &hdc, const RECT& rect, HBRUSH &hBrush){
    hBrush = CreateSolidBrush(clr);
    SelectObject(hdc, hBrush);

    Collision(rect);

    center.x += xSpeed; center.y += ySpeed;

    if(counter>0)
    {
        Rectangle(hdc, center.x-27, center.y-27, center.x+27, center.y+27 );
        SelectObject(hdc, GetStockObject(WHITE_BRUSH));
        DeleteObject(hBrush);
        return TRUE;
    }

    Ellipse(hdc, center.x-27, center.y-27, center.x+27, center.y+27 );
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    DeleteObject(hBrush);
    return TRUE;

}


