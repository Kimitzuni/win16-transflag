/*
 * Trans Flag in Win16
 *
 * Copyright (c) Rebecca White, 2023 <rwhitedev4@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "windows.h"
#include "hello.h"

char szAppName[10];
char szAbout[10];
char szMessage[15];
int MessageLength;

static HANDLE hInst;
FARPROC lpprocAbout;

RECT rcWnd;
HPEN hPen;

COLORREF cyan;
COLORREF pink;

long FAR PASCAL HelloWndProc(HWND, unsigned, WORD, LONG);

BOOL FAR PASCAL About( hDlg, message, wParam, lParam )
HWND hDlg;
unsigned message;
WORD wParam;
LONG lParam;
{
    if (message == WM_COMMAND) {
        EndDialog( hDlg, TRUE );
        return TRUE;
        }
    else if (message == WM_INITDIALOG)
        return TRUE;
    else return FALSE;
}


void HelloPaint( hDC )
HDC hDC;
{
    TextOut( hDC,
             (short)10,
             (short)10,
             (LPSTR)szMessage,
             (short)MessageLength );
}


/* Procedure called when the application is loaded for the first time */
BOOL HelloInit( hInstance )
HANDLE hInstance;
{
    PWNDCLASS   pHelloClass;

    /* Load strings from resource */
    LoadString( hInstance, IDSNAME, (LPSTR)szAppName, 10 );
    LoadString( hInstance, IDSABOUT, (LPSTR)szAbout, 10 );
    MessageLength = LoadString( hInstance, IDSTITLE, (LPSTR)szMessage, 15 );

    pHelloClass = (PWNDCLASS)LocalAlloc( LPTR, sizeof(WNDCLASS) );

    pHelloClass->hCursor        = LoadCursor( NULL, IDC_ARROW );
    pHelloClass->hIcon          = LoadIcon( hInstance, MAKEINTRESOURCE(HELLOICON) );
    pHelloClass->lpszMenuName   = (LPSTR)NULL;
    pHelloClass->lpszClassName  = (LPSTR)szAppName;
    pHelloClass->hbrBackground  = (HBRUSH)GetStockObject( WHITE_BRUSH );
    pHelloClass->hInstance      = hInstance;
    pHelloClass->style          = CS_HREDRAW | CS_VREDRAW;
    pHelloClass->lpfnWndProc    = HelloWndProc;

    if (!RegisterClass( (LPWNDCLASS)pHelloClass ) )
        /* Initialization failed.
         * Windows will automatically deallocate all allocated memory.
         */
        return FALSE;

    LocalFree( (HANDLE)pHelloClass );
    return TRUE;        /* Initialization succeeded */
}


int PASCAL WinMain( hInstance, hPrevInstance, lpszCmdLine, cmdShow )
HANDLE hInstance, hPrevInstance;
LPSTR lpszCmdLine;
int cmdShow;
{
    MSG   msg;
    HWND  hWnd;
    HMENU hMenu;

    if (!hPrevInstance) {
        /* Call initialization procedure if this is the first instance */
        if (!HelloInit( hInstance ))
            return FALSE;
        }
    else {
        /* Copy data from previous instance */
        GetInstanceData( hPrevInstance, (PSTR)szAppName, 10 );
        GetInstanceData( hPrevInstance, (PSTR)szAbout, 10 );
        GetInstanceData( hPrevInstance, (PSTR)szMessage, 15 );
        GetInstanceData( hPrevInstance, (PSTR)&MessageLength, sizeof(int) );
        }

    hWnd = CreateWindow((LPSTR)szAppName,
                        (LPSTR)szMessage,
                        WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT,    /*  x - ignored for tiled windows */
                        CW_USEDEFAULT,    /*  y - ignored for tiled windows */
                        300,    /* cx - ignored for tiled windows */
                        200,    /* cy - ignored for tiled windows */
                        (HWND)NULL,        /* no parent */
                        (HMENU)NULL,       /* use class menu */
                        (HANDLE)hInstance, /* handle to window instance */
                        (LPSTR)NULL        /* no params to pass on */
                        );

    /* Save instance handle for DialogBox */
    hInst = hInstance;

    /* Bind callback function with module instance */
    lpprocAbout = MakeProcInstance( (FARPROC)About, hInstance );

    /* Insert "About..." into system menu */
    hMenu = GetSystemMenu(hWnd, FALSE);
    ChangeMenu(hMenu, 0, NULL, 999, MF_APPEND | MF_SEPARATOR);
    ChangeMenu(hMenu, 0, (LPSTR)szAbout, IDSABOUT, MF_APPEND | MF_STRING);

    /* Make window visible according to the way the app is activated */
    ShowWindow( hWnd, cmdShow );
    UpdateWindow( hWnd );

    /* Polling messages from event queue */
    while (GetMessage((LPMSG)&msg, NULL, 0, 0)) {
        TranslateMessage((LPMSG)&msg);
        DispatchMessage((LPMSG)&msg);
        }

    return (int)msg.wParam;
}


/* Procedures which make up the window class. */
long FAR PASCAL HelloWndProc( hWnd, message, wParam, lParam )
HWND hWnd;
unsigned message;
WORD wParam;
LONG lParam;
{
    PAINTSTRUCT ps;

    switch (message)
    {
    case WM_SYSCOMMAND:
        switch (wParam)
        {
        case IDSABOUT:
            DialogBox( hInst, MAKEINTRESOURCE(ABOUTBOX), hWnd, lpprocAbout );
            break;
        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
        }
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    case WM_PAINT:
        BeginPaint( hWnd, (LPPAINTSTRUCT)&ps );
        // HelloPaint( ps.hdc );
		   
		GetClientRect(hWnd, &rcWnd);                                             
    	
    	/*
    	 * This whole section got rewritten to be, generally cleaner and just plain better.
    	 * And more than likely not cause memory leaks.
    	 *
    	 * If you want to see the horror that it was before I decided to rewrite it, you
    	 * can:
    	 *
    	 *	github.com/kimitzuni/win16-transflag/blob/bfa5/src/HELLO.C#L189
    	 *
    	 * It's bad!
    	 */
    	                                       
		cyan = RGB(0, 255, 255);
		pink = RGB(255, 0, 255);
		
		hPen = CreatePen(PS_SOLID, 1, cyan);
		SelectObject(ps.hdc, hPen);
		SetBkColor(ps.hdc, cyan);
		SelectObject(ps.hdc, CreateSolidBrush(cyan));
		Rectangle(ps.hdc, 0, 0, rcWnd.right, rcWnd.bottom / 5);
		Rectangle(ps.hdc, 0, rcWnd.bottom, rcWnd.right, (rcWnd.bottom / 5) * 4);
		
		hPen = CreatePen(PS_SOLID, 1, pink);
		SelectObject(ps.hdc, hPen);
		SetBkColor(ps.hdc, pink);
		SelectObject(ps.hdc, CreateSolidBrush(pink));
		Rectangle(ps.hdc, 0, (rcWnd.bottom / 5) * 2, rcWnd.right, rcWnd.bottom / 5);
		Rectangle(ps.hdc, 0, (rcWnd.bottom / 5) * 4, rcWnd.right, (rcWnd.bottom / 5) * 3);
		
		DeleteObject(hPen);
		EndPaint(hWnd, &ps);                          
        break;

    default:
        return DefWindowProc( hWnd, message, wParam, lParam );
        break;
    }
    return(0L);
}
