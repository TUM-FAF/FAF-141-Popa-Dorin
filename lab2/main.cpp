#include <windows.h>
#include <stdio.h>
#include "resource.h"


#define BUTTON_ADD_PLAYER         101
#define BUTTON_DISPLAY_PLAYER_NR  102
#define INPUT_TEXT_SHOW_PLAYER    103
#define INPUT_TEXT_ADD_PLAYER     104


LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND hPLAYERList;
HWND hInputPLAYER;
char PLAYER[500] = "";
char firstText[] = "Barca player's List : ";
int PLAYERNumber = 0;
static int scrollColor = 0;
static int widthScroll = 0;
static int heightScroll = 40;
HINSTANCE hInstance;
static int fontColor[3];





int WINAPI WinMain(HINSTANCE hInst,HINSTANCE hPrevInst,LPSTR lpCmdLine,int nShowCmd) {

    hInstance = hInst;
    HACCEL hAccel = LoadAccelerators(hInst, MAKEINTRESOURCE(ID_ACCELERATOR));

    WNDCLASSEX wClass;

    wClass.hInstance = hInst;
    wClass.lpszClassName = "Window Class";
    wClass.lpfnWndProc = (WNDPROC)WinProc;
    wClass.style = CS_HREDRAW|CS_VREDRAW;
    wClass.cbSize = sizeof(WNDCLASSEX);
    wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 255, 5));
    wClass.hCursor = LoadCursor(NULL, IDC_HELP);
    wClass.hIconSm = NULL;
    wClass.lpszMenuName  = MAKEINTRESOURCE(IDR_MYMENU);
    wClass.hIcon  = LoadIcon (GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON));
    wClass.cbClsExtra = 0;                                                         // No extra bytes after the window class
    wClass.cbWndExtra = 0;

    HMENU hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MYMENU));

    wClass.lpszMenuName = NULL;



    if (!RegisterClassEx(&wClass)) {
        GetLastError();
        MessageBox(NULL,
            "Window class creation failed\r\n",
            "Window Class Failed",
            MB_ICONERROR);
    }

    HWND hWnd=CreateWindowEx(NULL,
            "Window Class",
            "Laboratory Work #2 Dorin Popa",
            WS_OVERLAPPEDWINDOW,
            400,
            200,
            600,
            400,
            NULL,
            hmenu,
            hInst,
            NULL);



    if(!hWnd) {
        GetLastError();

        MessageBox(NULL,
            "Window creation failed\r\n",
            "Window Creation Failed",
            MB_ICONERROR);
    }

    ShowWindow(hWnd,nShowCmd);

    MSG msg;





    while (GetMessage (&msg, NULL, 0, 0)) {
        if (!TranslateAccelerator (hWnd, hAccel, &msg)) {
            TranslateMessage (&msg) ;
            DispatchMessage (&msg) ;
       }
    }



    return 0;

}

LRESULT CALLBACK WinProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam) {
    PAINTSTRUCT Ps;
    static HWND hWndList;
    static HWND hWndScroll, hWndWidthScroll, hWndHeightScroll;
    static RECT rcScroll, rcPLAYERList, rcInputPLAYER, rcQuantity;
    HBRUSH hBrushStatic;
    HBRUSH BrushBlue;



    SetRect(&rcScroll, 315, 40, 25, 250);
    SetRect(&rcPLAYERList, 10, 10, 200, 40);
    SetRect(&rcInputPLAYER, 120, 150, 190, 25);
    SetRect(&rcQuantity, 210, 10, 300, 30);


    switch(msg) {
    case WM_CREATE: {

                //Create Scrolls


                hWndWidthScroll = CreateWindowEx((DWORD)NULL,
                    TEXT("scrollbar"),
                    NULL,
                    WS_CHILD | WS_VISIBLE | SBS_HORZ,
                    10, 160, 300, 20,
                    hWnd,
                    (HMENU)ID_WIDTH_SCROLL,
                    hInstance,
                    NULL);
                SetScrollRange(hWndWidthScroll, SB_CTL, 0, 100, TRUE);
                SetScrollPos(hWndWidthScroll, SB_CTL, 0, TRUE);

                hWndHeightScroll = CreateWindowEx((DWORD)NULL,
                    TEXT("scrollbar"),
                    NULL,
                    WS_CHILD | WS_VISIBLE | SBS_HORZ,
                    10, 185, 300, 20,
                    hWnd,
                    (HMENU)ID_HEIGHT_SCROLL,
                    hInstance,
                    NULL);
                SetScrollRange(hWndHeightScroll, SB_CTL, 0, 100, TRUE);
                SetScrollPos(hWndHeightScroll, SB_CTL, 45, TRUE);

                /**
                * Create ListBox
                */

                hWndList = CreateWindowEx((DWORD)NULL,
                    TEXT("listbox"),
                    "",
                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_AUTOVSCROLL | LBS_STANDARD | WS_BORDER,
                    10, 40,
                    350, 100,
                    hWnd,
                    (HMENU) IDC_PLAYER_LIST,
                    hInstance,
                    NULL);


                /**
                * Create AddPLAYER Button
                */
                HFONT hFont = CreateFont(30,0,0,0,FW_DONTCARE,FALSE,TRUE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS,
                    CLIP_DEFAULT_PRECIS,NULL, VARIABLE_PITCH,TEXT("Impact"));

                HWND hButtonAddPLAYER = CreateWindowEx(NULL,
                    "BUTTON",
                    "Add the player",
                    WS_TABSTOP|WS_VISIBLE|
                    WS_CHILD|BS_DEFPUSHBUTTON|BS_TOP,
                    380,
                    100,
                    100,
                    25,
                    hWnd,
                    (HMENU)BUTTON_ADD_PLAYER,
                    GetModuleHandle(NULL),
                    NULL);

                /**
                * Create button ShowPLAYERNumber
                */
                HWND hShowPLAYERNumber = CreateWindowEx(NULL,
                    "BUTTON",
                    "FC Barcelona info",
                    WS_TABSTOP|WS_VISIBLE|
                    WS_CHILD|BS_DEFPUSHBUTTON|BS_TOP,
                    360,
                    160,
                    200,
                    40,
                    hWnd,
                    (HMENU)BUTTON_DISPLAY_PLAYER_NR,
                    GetModuleHandle(NULL),
                    NULL);
                SendMessage (hShowPLAYERNumber, WM_SETFONT, WPARAM (hFont), TRUE);

                /**
                * Draw main Input PLAYER field
                */

                hInputPLAYER = CreateWindowEx(
                    (DWORD)NULL,
                    TEXT("edit"),
                    "",
                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                    380,
                    70,
                    190,
                    25,
                    hWnd,
                    (HMENU)INPUT_TEXT_ADD_PLAYER,
                    GetModuleHandle(NULL),
                    NULL);

                /**create add player info field**/
                CreateWindowEx(0, TEXT("static"), "Input player beyond",
                WS_VISIBLE | WS_CHILD | SS_CENTER,
                380, 42, 150, 17,
                hWnd, (HMENU)0, hInstance, NULL);

            }
            break;

    case WM_PAINT: {
            HDC hdc = BeginPaint(hWnd, &Ps);

            /**
            * Draw Text
            */

            // Second Text
            char PLAYERNrMessage[40];
            char nr[50];
            LoadString (hInstance, IDS_PLAYERNUMBER, PLAYERNrMessage, 40) ;
            wsprintf (nr, PLAYERNrMessage, PLAYERNumber);

            SetBkMode(hdc, TRANSPARENT);

            DrawText( hdc, nr, -1, &rcQuantity, DT_SINGLELINE | DT_NOCLIP) ;
            SetBkMode(hdc, OPAQUE);
            SetTextColor(hdc, RGB(fontColor[0], fontColor[1], fontColor[2]));
            DrawText(hdc, TEXT(firstText), -1, &rcPLAYERList, DT_NOCLIP);

            EndPaint(hWnd, &Ps);
        }
        break;


    case WM_COMMAND: {
        switch(LOWORD(wParam)) {
        case BUTTON_ADD_PLAYER: {

                char buffer[256];
                SendMessage(hInputPLAYER,
                    WM_GETTEXT,
                    sizeof(buffer)/sizeof(buffer[0]),
                    reinterpret_cast<LPARAM>(buffer));


                if (strlen(buffer) > 0){
                    char newInput[255] = "- ";

                    strcat(newInput, buffer);

                    SendMessage(hWndList, LB_ADDSTRING, 0, (LPARAM)newInput);
                    SendMessage(hInputPLAYER, WM_SETTEXT, NULL, (LPARAM)"");
                    PLAYERNumber++;
                    InvalidateRect(hWnd, &rcQuantity, TRUE);

                }
            }
            break;

        case BUTTON_DISPLAY_PLAYER_NR: {
                char buffer[255] = "";

                switch(PLAYERNumber){
                case 0:
                    strcat(buffer, "You dont't have any player. You need 11 to play");
                    break;
                case 1:
                    strcat(buffer, "Not enough players. 10 left!");
                    break;
                case 2:
                    strcat(buffer, "Not enough players. 9 left!");
                    break;
                case 3:
                    strcat(buffer, "Not enough players. 8 left!");
                    break;
                case 4:
                    strcat(buffer, "Not enough players. 7 left!");
                    break;
                case 5:
                    strcat(buffer, "Not enough players. 6 left!");
                    break;
                case 7:
                    strcat(buffer, "Not enough players. 5 left!");
                    break;
                case 8:
                    strcat(buffer, "Not enough players. 4 left!");
                    break;
                case 9:
                    strcat(buffer, "Not enough players. 3 left!");
                    break;
                case 10:
                    strcat(buffer, "Not enough players. 2 left!");
                    break;
                case 11:
                    strcat(buffer, "Not enough players. 1 left!");
                    break;
                default:
                    strcat(buffer, "Now your squad is ready for clasico!");
                    break;
                }
                MessageBox(NULL,
                    buffer,
                    "Requirements",
                    MB_ICONINFORMATION);
            }
            break;
        case ID_FILE_EXIT: {
                PostQuitMessage(0);
            }
            break;
        case ID_STUFF_ABOUT: {
                char aboutText[255] = "FC Barcelona is the best team in the world. Won 5 times the Uefa Champions League, last one was in 2015";
                MessageBox(NULL,
                    aboutText,
                    "About FCB",
                    MB_ICONINFORMATION);
            }
            break;
        case ID_EVENT_RED: {
                fontColor[0] = 255;
                fontColor[1] = 0;
                fontColor[2] = 0;
                InvalidateRect(hWnd, &rcPLAYERList, TRUE);
            }
            break;
        case ID_EVENT_GREEN: {
                fontColor[0] = 0;
                fontColor[1] = 255;
                fontColor[2] = 0;
                InvalidateRect(hWnd, &rcPLAYERList, TRUE);
            }
            break;
        case ID_EVENT_BLUE: {
                fontColor[0] = 0;
                fontColor[1] = 0;
                fontColor[2] = 255;
                InvalidateRect(hWnd, &rcPLAYERList, TRUE);
            }
            break;

        case IDC_PLAYER_LIST:{
                if (HIWORD(wParam) == LBN_DBLCLK) {
                    int index = SendMessage(hWndList, LB_GETCURSEL, 0, 0);
                    SendMessage(hWndList, LB_DELETESTRING, (WPARAM)index, 0);
                    PLAYERNumber--;
                    InvalidateRect(hWnd, &rcQuantity, TRUE);
                }
            }
            break;
        }
    }
    break;




    case WM_HSCROLL: {
            RECT rect;
            GetWindowRect(hWnd, &rect);
            int iSysWidth = GetSystemMetrics(SM_CXSCREEN);
            int iSysHeight = GetSystemMetrics(SM_CYSCREEN);
            int iWinWidth = rect.right - rect.left;
            int iWinHeight = rect.bottom - rect.top;

            switch (GetWindowLong((HWND)lParam, GWL_ID)) {
            case ID_WIDTH_SCROLL: {
                    switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        widthScroll -= 1;
                        break;
                    case SB_LINERIGHT:
                        widthScroll += 1;
                        break;
                    case SB_THUMBPOSITION:
                        widthScroll = HIWORD(wParam);
                        break;
                    default:
                        break;
                    }
                    SetScrollPos(hWndWidthScroll, SB_CTL, widthScroll, TRUE);
                    MoveWindow(hWnd, rect.left, rect.top, (widthScroll * iSysWidth / 100), iWinHeight, TRUE);
                }
                break;
            case ID_HEIGHT_SCROLL: {
                    switch(LOWORD(wParam)) {
                    case SB_LINELEFT:
                        widthScroll--;
                        break;
                    case SB_LINERIGHT:
                        widthScroll++;
                        break;
                    case SB_THUMBPOSITION:
                        widthScroll = HIWORD(wParam);
                        break;
                    default:
                        break;
                    }
                    SetScrollPos(hWndHeightScroll, SB_CTL, widthScroll, TRUE);
                    MoveWindow(hWnd, rect.left, rect.top, iWinWidth, (widthScroll * iSysHeight / 100), TRUE);
                }
                break;
            }
        }
        break;



    case WM_KEYDOWN: {
            switch (wParam) {

            case 0x42 : {   // 0x42 is the virtual key for "B" character
                    if (HIBYTE(GetAsyncKeyState(VK_LCONTROL))) {
                    BrushBlue = CreateSolidBrush(RGB(30, 50, 60));
                    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)BrushBlue);
                    InvalidateRect(hWnd, NULL, TRUE);
                    }
                }
                break;
            case VK_BACK: {
                    if (HIBYTE(GetAsyncKeyState(VK_LCONTROL))) {

                        SendMessage(hWndList, LB_RESETCONTENT, 0, 0);
                        PLAYERNumber = 0;
                        InvalidateRect(hWnd, &rcQuantity, TRUE);

                    }
                }
                break;
            }
        }
        break;

    case WM_SETFOCUS: {
            SetFocus(hWnd);
        }
        break;
    case WM_DESTROY: {
            PostQuitMessage(0);
            return 0;
        }
        break;
    }



    return DefWindowProc(hWnd,msg,wParam,lParam);
}
