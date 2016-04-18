#include <windows.h>
#include "resource.h"
#include "object.h"



LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

static Object *ptrObj[30];  // pointer to Object class of 30 size (30 objects maximum)
char szClassName[ ] = "WindowsApp";

int WINAPI WinMain (HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hWnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;

    wincl.hbrBackground =NULL;
COLORREF clr;
    if (!RegisterClassEx (&wincl))
        return 0;

    hWnd = CreateWindowEx (
           0,
           szClassName,
           "Laboratory #4",
           WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           700,
           700,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hWnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static PAINTSTRUCT ps;
    static HDC hdc;

    static HDC hdcMem;
    static RECT rect;
    static HBRUSH hBrush;
    static HBITMAP hbmMem;

    static HANDLE hOld;

    static int timerSpeed = 1;
    static int nrObj = 0;

    int counter;

    switch (msg)
    {
        case WM_CREATE:
        {
          hdc = GetDC(hWnd);
          GetClientRect(hWnd,&rect);

          SetTimer(hWnd, ID_TIMER, timerSpeed, NULL);
        break;
        }

        case WM_SIZE:
        {
            hdc = GetDC(hWnd);
            GetClientRect(hWnd, &rect);
        break;
        }

        case WM_LBUTTONDOWN:
        {
            POINT coord;
            coord.x = LOWORD(lParam);
            coord.y = HIWORD(lParam);
            counter=0;
            if (nrObj>0)
            {
                for(int i = 0; i<nrObj; i++)
                {
                    if(abs(coord.x-ptrObj[i]->center.x)<52)
                    {
                        counter+=1;
                    }
                }
                if(counter==0)
                {
                    ptrObj[nrObj] = new Circle(coord,2 + coord.x%5);
                    ptrObj[nrObj] -> Color(RGB(coord.x%200, coord.x%150+coord.y%100, coord.y%200));

                    nrObj++;
                }
            }
            else
            {
                ptrObj[nrObj] = new Circle(coord,2 + coord.x%5);
                ptrObj[nrObj] -> Color(RGB(coord.x%200, coord.x%150+coord.y%100, coord.y%200));

                nrObj++;
            }
        break;
        }

         case WM_KEYDOWN:
         {
            switch(wParam)
            {
                case VK_DOWN:
                {
                    timerSpeed+=20;
                break;
                }

                case VK_UP:
                {
                    timerSpeed-=20;

                        if (timerSpeed < 0)
                        {
                            timerSpeed = 1;
                        }
                 break;
                }

                default: return DefWindowProc (hWnd, msg, wParam, lParam);
            break;
            }

            KillTimer(hWnd,ID_TIMER);
            SetTimer(hWnd,ID_TIMER,timerSpeed,NULL);
        break;
        }


        case WM_PAINT:
        {
            hdc = BeginPaint(hWnd,&ps);
            GetClientRect(hWnd,&rect);

            hdcMem = CreateCompatibleDC(hdc);
            hbmMem = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
            hOld = SelectObject(hdcMem, hbmMem);

            for(int i = 0; i<nrObj-1; i++)
            {
                for(int j = i+1; j < nrObj; j++)
                {
                    Interaction(*ptrObj[i],*ptrObj[j]);
                }
            }

            FillRect(hdcMem, &rect,(HBRUSH)GetStockObject(BLACK_BRUSH));

            for(int i = 0; i < nrObj; i++)
            {
                ptrObj[i] -> Move(hdcMem, rect, hBrush);
            }

            BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, SRCCOPY);

            SelectObject(hdcMem,hOld);
            DeleteObject(hbmMem);
            DeleteDC(hdcMem);

            EndPaint(hWnd,&ps);

        break;
        }

        case WM_ERASEBKGND:
            return 1;
        break;

        case WM_TIMER:
        {
            InvalidateRect(hWnd,NULL,FALSE);
        break;
        }

        case WM_DESTROY:
        {
            KillTimer(hWnd,ID_TIMER);

            PostQuitMessage (0);
        break;
        }

        default:
            return DefWindowProc (hWnd, msg, wParam, lParam);
    }
    return 0;
}
