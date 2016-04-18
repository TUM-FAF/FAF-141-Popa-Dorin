#include <iostream>
#include <windows.h>
#include <cmath>

class Object
{

protected:
    COLORREF clr;
public:
    POINT center;
    int xSpeed,ySpeed;
    int counter=0;

    Object(POINT center,const int &speed);
    bool Accelerate(const int& deltaSpeedX, const int& deltaSpeedY);
    bool Color(const COLORREF &clr);
    bool Collision(const RECT &rect);
    bool Shape(Object &ob);
    virtual bool Move(const HDC &hdc, const RECT& rect,HBRUSH &hBrush) = 0;
};

class Circle : public Object {
public:
    Circle(POINT center,const int &speed): Object(center,speed){}
    bool Move(const HDC &hdc,const RECT& rect,HBRUSH &hBrush);
};

bool Interaction(Object &obj1, Object &obj2);
