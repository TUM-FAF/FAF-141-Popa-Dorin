	#include <tchar.h>
	#include <windows.h>
	#include <stdlib.h>
	#include <time.h>
	#define IDC_TEXT1 101
	#define IDC_BUTTON1 102
	#define IDC_BUTTON2 103
	#define IDC_TEXT2 104
	#define IDC_BUTTON3 105
	#define IDC_BUTTON4 106
	#define IDC_BUTTON5 107


	/*  Declare Windows procedure  */
	LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);


	/*  Make the class name into a global variable  */
	TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");


	int WINAPI WinMain (HINSTANCE hThisInstance,
	                     HINSTANCE hPrevInstance,
	                     LPSTR lpszArgument,
	                     int nCmdShow)
	{
	    HWND hwnd;               /* This is the handle for our window */
	    MSG messages;            /* Here messages to the application are saved */
	    WNDCLASSEX wincl;        /* Data structure for the windowclass */


	    /* The Window structure */
	    wincl.hInstance = hThisInstance;
	    wincl.lpszClassName = szClassName;
	    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	    wincl.style = CS_VREDRAW | CS_HREDRAW;                 /* Catch double-clicks */
	    wincl.cbSize = sizeof (WNDCLASSEX);


	    /* Use default icon and mouse-pointer */
	    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
	    wincl.lpszMenuName = NULL;                 /* No menu */
	    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	    wincl.cbWndExtra = 0;                      /* structure or the window instance */
	    /* Use Windows's default colour as the background of the window */
	    wincl.hbrBackground = CreateSolidBrush(RGB(255,0,0)); // SETTING BACKGROUND COLOR


	    /* Register the window class, and if it fails quit the program */
	    if (!RegisterClassEx (&wincl))
	        return 0;


	    /* The class is registered, let's create the program*/
	    hwnd = CreateWindowEx (
	           0,                   /* Extended possibilites for variation */
	           szClassName,         /* Classname */
	           _T("Windows Programming laboratory#1"),       /* Title Text */
	           WS_OVERLAPPEDWINDOW, /* default window */
	           411,       /* Windows decides the position */
	           179,       /* where the window ends up on the screen */
	           544,                 /* The programs width */
	           375,                 /* and height in pixels */
	           HWND_DESKTOP,        /* The window is a child-window to desktop */
	           NULL,                /* No menu */
	           hThisInstance,       /* Program Instance handler */
	           NULL                 /* No Window Creation data */
	           );


	    /* Make the window visible on the screen */
	    ShowWindow (hwnd, nCmdShow);


	    /* Run the message loop. It will run until GetMessage() returns 0 */
	    while (GetMessage (&messages, NULL, 0, 0))
	    {
	        /* Translate virtual-key messages into character messages */
	        TranslateMessage(&messages);
	        /* Send message to WindowProcedure */
	        DispatchMessage(&messages);
	    }


	    /* The program return-value is 0 - The value that PostQuitMessage() gave */
	    return messages.wParam;
	}




	/*  This function is called by the Windows function DispatchMessage()  */


	LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	    HDC hdc = NULL;
	    PAINTSTRUCT ps;
	    RECT rect;
	    HFONT fontCorbel, fontText1, fontText2, buttonFont,
	          temp1, temp2;
	    static HWND textArea1, buttonSubmit, buttonClear,
	           textArea2, buttonRed, buttonGreen, buttonBlue;
	    HBRUSH textArea1Brush;
	    static int cxCoord, cyCoord;
	    static HGDIOBJ defaultFont;
	    LRESULT textSize, textSize2;
	    char textStore[1000];
	    static bool textFlagRed, textFlagBlue, textFlagGreen;
	    static bool backgFlag;
	    static int a, b, c;






	    switch (message)                  /* handle the messages */
	    {
	        case WM_CREATE:
	        {
	            textArea1 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
	                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_TEXT1, GetModuleHandle(NULL), NULL);
	            buttonSubmit = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Submit"),
	                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_BUTTON1, GetModuleHandle(NULL), NULL);
	            buttonClear =  CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Clear"),
	                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_BUTTON2, GetModuleHandle(NULL), NULL);
	            textArea2 = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("EDIT"), TEXT(" "),
	                                       WS_VISIBLE | WS_CHILD | ES_MULTILINE | ES_AUTOVSCROLL | WS_VSCROLL | ES_READONLY,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_TEXT1, GetModuleHandle(NULL), NULL);
	            buttonRed = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Red"),
	                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_BUTTON3, GetModuleHandle(NULL), NULL);
	            buttonGreen = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Green"),
	                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_BUTTON4, GetModuleHandle(NULL), NULL);
	            buttonBlue = CreateWindowEx(NULL, TEXT("BUTTON"), TEXT("Blue"),
	                                       WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
	                                       0, 0, 0, 0,
	                                       hwnd, (HMENU)IDC_BUTTON5, GetModuleHandle(NULL), NULL);
	            HGDIOBJ defaultFont = GetStockObject(DEFAULT_GUI_FONT);
	            SendMessage(textArea1, WM_SETTEXT, NULL, (LPARAM)"oleg - you can erase and write what you want");
	            SendMessage(buttonSubmit, WM_SETFONT, (WPARAM)defaultFont, MAKELPARAM(FALSE,0));
	            SendMessage(buttonClear, WM_SETFONT, (WPARAM)defaultFont, MAKELPARAM(FALSE,0));
	            break;
	        }



	        case WM_PAINT:
	        {
	            hdc = BeginPaint(hwnd, &ps);
	            fontCorbel = CreateFont(20, 0, 0, 0, FW_BOLD, false, false, false,
	                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	                                    DEFAULT_QUALITY, FF_DONTCARE, "Corbel");
	            SetBkMode(hdc, TRANSPARENT);
	            GetClientRect(hwnd, &rect);
	            fontText1 = (HFONT)SelectObject(hdc, fontCorbel);
                	            buttonFont = CreateFont(20, 0, 0, 0, FW_DONTCARE, false, false, false,
	                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	                                    DEFAULT_QUALITY, FF_DONTCARE, "Consolas");

	            SendMessage(buttonRed, WM_SETFONT, WPARAM(buttonFont), TRUE);
	            SendMessage(buttonGreen, WM_SETFONT, WPARAM(buttonFont), TRUE);
	            SendMessage(buttonBlue, WM_SETFONT, WPARAM(buttonFont), TRUE);
	            temp2 = CreateFont(14, 0, 0, 0, FW_DONTCARE, false, false, false,
	                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	                                    DEFAULT_QUALITY, FF_DONTCARE, "Arial");

	            temp1 = (HFONT)SelectObject(hdc, temp2);
	            SetTextColor(hdc, RGB(10, 0, 255));    /* the text from the center  */
	            DrawText(hdc, TEXT("Done with Pride and Prejudice by Dorin Popa"), -1, &rect, DT_SINGLELINE| DT_CENTER| DT_TOP);
	            EndPaint(hwnd, &ps);
	            break;
	        }


	        case WM_GETMINMAXINFO:
	        {
	            LPMINMAXINFO winSize = (LPMINMAXINFO)lParam;
	            winSize->ptMinTrackSize.x = 510;
	            winSize->ptMinTrackSize.y = 375;
	            winSize->ptMaxTrackSize.x = 630;
	            winSize->ptMaxTrackSize.y = 425;
	            break;
	        }


	        case WM_COMMAND:
	            switch(LOWORD(wParam))
	            {
	                case IDC_BUTTON1:
	                {
	                    textSize = SendMessage(textArea1, WM_GETTEXT, 100, (LPARAM)textStore); // text size
	                    textStore[textSize] = _T('\0'); // initialization with null character
	                    SendMessage(textArea2, EM_REPLACESEL, 0, (LPARAM)textStore); // add inputed text to window
	                    SendMessage(textArea2, EM_REPLACESEL, 0, (LPARAM)" ");
	                    RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_ERASE);
	                    fontCorbel = CreateFont(20, 0, 0, 0, FW_DONTCARE, false, false, false,
	                                    DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
	                                    DEFAULT_QUALITY, FF_DONTCARE, "Corbel");
	                    SendMessage(textArea2, WM_SETFONT, (WPARAM)fontCorbel, TRUE);
	                    break;
	                }


	                case IDC_BUTTON2:
	                {
	                    SendMessage(textArea2, WM_SETTEXT, NULL, NULL);
	                    break;
	                }


	                case IDC_BUTTON3:
	                {
	                    textFlagRed = true;
	                    textFlagBlue = false;
	                    textFlagGreen = false;
	                    InvalidateRect(textArea2, NULL, TRUE);
	                    break;
	                }


	                case IDC_BUTTON4:
	                {
	                    textFlagGreen = true;
	                    textFlagBlue = false;
	                    textFlagRed = false;
	                    InvalidateRect(textArea2, NULL, TRUE);
	                    break;
	                }


	                case IDC_BUTTON5:
	                {
	                    textFlagBlue = true;
	                    textFlagRed = false;
	                    textFlagGreen = false;
	                    InvalidateRect(textArea2, NULL, TRUE);
	                    break;
	                }
	                }
	        break;


	        case WM_SYSCOMMAND:
	        {
	            switch(wParam)
	            {
	                case SC_MINIMIZE:
	                {
	                    srand(time(NULL));
	                    a = rand() % 255 + 1;
	                    b = rand() % 255 + 1;
	                    c = rand() % 255 + 1;
	                    backgFlag = true;
	                    if(backgFlag == true)
	                    {
	                        SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(a, b, c)));
	                    }
	                    InvalidateRect(hwnd, NULL, TRUE);
	                    break;
	                }


	                case SC_MAXIMIZE:
	                {
	                    double i = 20;
	                    while (i < 330)
	                    {
	                        SetWindowPos(hwnd, HWND_TOP, 411, i,544, 375, SWP_SHOWWINDOW);
	                        i = i + 0.1;
	                    }
	                    while (i > 20)
	                    {
	                        SetWindowPos(hwnd, HWND_TOP, 411, i,544, 375, SWP_SHOWWINDOW);
	                        i = i - 0.1;
	                    }
	                    break;
	                 }


	                 case SC_CLOSE:
	                 {
	                    if(MessageBox(hwnd, "How do you do Irina?", "Oleg", MB_YESNO) == IDYES)
	                        {
	                            exit(1);
	                        }
	                        break;
	                 }


	                 default:
	                     return DefWindowProc(hwnd, message, wParam, lParam);
	                }
	            break;


	        case WM_SIZE:
	        {
	            cxCoord = LOWORD(lParam); // 544
	            cyCoord = HIWORD(lParam); // 375
	            MoveWindow(textArea1, 20, 45, cxCoord-40, cyCoord/2-97, TRUE);
	            MoveWindow(buttonSubmit, 20, cyCoord/2-40, cxCoord-430, cyCoord/2-144, TRUE);
	            MoveWindow(buttonClear, 411, cyCoord/2-40, cxCoord-430, cyCoord/2-144, TRUE);
	            MoveWindow(textArea2, 20, cyCoord-170, cxCoord-40, cyCoord/2-97, TRUE);
	            MoveWindow(buttonRed, 20, (cyCoord-200) + cyCoord/2-55, cxCoord-425, cyCoord/2-135, TRUE);
	            MoveWindow(buttonBlue, 406, (cyCoord-200) + cyCoord/2-55, cxCoord-425, cyCoord/2-135, TRUE);
	            MoveWindow(buttonGreen, 213, (cyCoord-200) + cyCoord/2-55, cxCoord-425, cyCoord/2-135, TRUE);
	            break;
	        }


	        case WM_CTLCOLOREDIT:
	        {
	            if(IDC_TEXT1 == GetDlgCtrlID((HWND)lParam))
	            {
	                textArea1Brush = CreateSolidBrush(RGB(204, 153, 153));
	                SetBkMode((HDC)wParam, TRANSPARENT);
	                return(INT_PTR)textArea1Brush;
	            }
	            break;
	        }


	        case WM_CTLCOLORSTATIC:
	        {
	            if(textFlagRed == true && (HWND)lParam == textArea2)
	            {
	                HBRUSH hbr = (HBRUSH) DefWindowProc(hwnd, message, wParam, lParam);
	                SetTextColor((HDC) wParam, RGB(255, 0, 0));
	                return (BOOL) hbr;
	            }
	            else if(textFlagBlue == true && (HWND)lParam == textArea2)
	            {
	                HBRUSH hbr = (HBRUSH) DefWindowProc(hwnd, message, wParam, lParam);
	                SetTextColor((HDC) wParam, RGB(0, 0, 255));
	                return (BOOL) hbr;
	            }
	            else if(textFlagGreen == true && (HWND)lParam == textArea2)
	            {
	                HBRUSH hbr = (HBRUSH) DefWindowProc(hwnd, message, wParam, lParam);
	                SetTextColor((HDC) wParam, RGB(0, 163, 82));
	                return (BOOL) hbr;
	            }
	            break;
	        }


	        case WM_DESTROY:
	        {
	            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
	            break;
	        }


	        default:                      /* for messages that we don't deal with */
	            return DefWindowProc (hwnd, message, wParam, lParam);
	    }


	    return 0;
	} }
