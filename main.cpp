#include <windows.h>

#define HELP_MENU_NEW 100
#define HELP_MENU_EXIT 101

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu; // global main menu bar
HWND hEditUsername, hEditPassword, hButtonSubmit; // global handlers

/*
// WinMain - main() function for win32 applications
// called by OS when running program
//
// hInst - window instance received from OS
// hPrevInst - previous instance
// args - arguments passed as string
// nCmdShow - number of arguments passed
*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
    LPCSTR CLASS_NAME = "parentWindow"; // instance name

    WNDCLASS wc = {0}; // initialize all values to 0
    wc.hbrBackground    = (HBRUSH)COLOR_WINDOW;
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon            = LoadIcon(NULL, IDI_QUESTION);
    wc.hInstance        = hInst;
    wc.lpszClassName    = CLASS_NAME;
    wc.lpfnWndProc      = WindowProc;

    if (!RegisterClass(&wc))
    {
        return -1;
    }

    CreateWindow(CLASS_NAME, "Login Prompt",        // window class name, window title
                WS_VISIBLE | WS_OVERLAPPEDWINDOW,   // style
                100, 100, 400, 250,                 // x & y origin, window width & height
                NULL, NULL, NULL, NULL
                );

    MSG msg = {0};
    while (GetMessage(&msg, NULL, NULL, NULL)) // event loop
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); // dispatch message to WindowProc (window procedure)
    }

    return 0;
}

/*
// WindowProc - handles all messages sent from event loop
//
// hWnd - window handler
// msg - message passed from event loop
// wParam - menu item id is passed via wParam
// lParam -
*/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_CREATE: // message sent when window is initially created
        AddMenus(hWnd);
        AddControls(hWnd);
        break;
    case WM_COMMAND:
        switch(wParam)
        {
        case HELP_MENU_NEW:
            MessageBeep(MB_OK);
            break;
        case HELP_MENU_EXIT:
            DestroyWindow(hWnd); // sends WM_DESTROY message via event loop
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // returns false to GetMessage() to end event loop
        break;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam); // handle default messages
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu(); // returns empty menu instance
    HMENU hHelpMenu = CreateMenu();

    AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_NEW, "About");
    AppendMenu(hHelpMenu, MF_STRING, NULL, NULL);
    AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

    SetMenu(hWnd, hMenu); // specify handler to which menu is to be added
}


// controls are child windows of the parent window
void AddControls(HWND hWnd)
{

    CreateWindow("Static", "Username: ",    // predefined class name - static text, window label
                  WS_VISIBLE | WS_CHILD,    // style - specify it as a child style
                  75, 50, 125, 25,          // x & y with respect to parent window, child instance width & height
                  hWnd, NULL, NULL, NULL    // parent handler
                );

    hEditUsername = CreateWindow("Edit", "",                            // predefined class name - edit box, box text
                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,   // style - specify it as a child style
                  150, 50, 125, 25,                                     // x & y with respect to parent window, child instance width & height
                  hWnd, NULL, NULL, NULL                                // parent handler
                );

    CreateWindow("Static", "Password: ",    // predefined class name - static text, window label
                  WS_VISIBLE | WS_CHILD,    // style - specify it as a child style
                  75, 75, 125, 25,          // x & y with respect to parent window, child instance width & height
                  hWnd, NULL, NULL, NULL    // parent handler
                );

    hEditPassword = CreateWindow("Edit", "",                             // predefined class name - edit box, box text
                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,    // style - specify it as a child style
                  150, 75, 125, 25,                                      // x & y with respect to parent window, child instance width & height
                  hWnd, NULL, NULL, NULL                                 // parent handler
                );

    hButtonSubmit = CreateWindow("Button", "Submit",    // predefined class name - button, button label
                 WS_VISIBLE | WS_CHILD,                 // style - specify it as a child style
                 225, 110, 50, 25,                      // x & y with respect to parent window, child instance width & height
                 hWnd, NULL, NULL, NULL);               // parent handler,
}
