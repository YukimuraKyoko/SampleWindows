#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>

/*
Self notes:
CreateWindow parameters: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632679(v=vs.85).aspx

*/


HWND textfield, button, textbox;
int winWidth = 800;
int winHeight = 600;
char szClassName[] = "TextEntry";
char textSaved[20];

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
//TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

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
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Auto Freak Database"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           winWidth,                 /* The programs width */
           winHeight,                 /* and height in pixels */
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
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:

        //Creates a static text box at position (20,20) in x,y coordinates
        //with 100 as the width and 20 as the height
        textfield = CreateWindow("STATIC",
                                 "Auto Freak", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 20, 20, 100, 20,
                                 hwnd, NULL, NULL, NULL);

        //Creates a pop up window with text
        button = CreateWindow("BUTTON",
                              "Pop up",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              20, 100, 200, 20,
                              hwnd, (HMENU)1, NULL, NULL);

        //Creates a button to close the window
        button = CreateWindow("BUTTON",
                              "Close",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              20, 400, 80, 20,
                              hwnd, (HMENU)2, NULL, NULL);

        //Creates a textbox to type in a string
        textbox = CreateWindow("EDIT",
                               "",
                               WS_VISIBLE | WS_CHILD | WS_BORDER,
                               winWidth/2, winHeight/2, 200, 20,
                               hwnd, NULL, NULL, NULL);
        //Storing the string from textbox
        CreateWindow("BUTTON",
                     "Go",
                     WS_VISIBLE | WS_CHILD | WS_BORDER,
                     winWidth/2 + 210, winHeight/2, 70, 20,
                     hwnd, (HMENU)3, NULL, NULL);

            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
            case 1:
                ::MessageBox(hwnd,"Button was clicked", "Button was clicked", MB_OK);
                break;
            case 2:
                PostQuitMessage (0);
                break;
            case 3:
                int getText = 0;
                char *t = &textSaved[0];
                getText = GetWindowText(textbox, &textSaved[0] ,20);

                ::MessageBox(hwnd, textSaved, textSaved, MB_OK);
                break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
