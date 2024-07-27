#include <windows.h>

#define HELP_MENU_ABOUT 100
#define HELP_MENU_EXIT 101
#define CHECKBOX_REMEMBER_ME 102

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void Setup(HINSTANCE);
void CreateMenuBar(HWND);
void CreateLoginPrompt(HWND);
void HandleCommandEvents(HWND, WPARAM);

HINSTANCE hInstance; // current instance
HMENU hMenu; // main menu bar
HWND hEditUsername, hEditPassword, hButtonSubmit, hButtonRememberMe; // login prompt handlers
bool isRememberMeChecked = false;

/*
// WinMain() - main() function for win32 applications
// called by OS when running program
//
// hInst - window instance received from OS
// hPrevInst - previous instance
// args - arguments passed as string
// nCmdShow - number of arguments passed
*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow)
{
    Setup(hInst);

    LPCSTR CLASS_NAME = "parentWindow"; // instance name

    WNDCLASS wc = {0};                                  // initialize all values to 0
    wc.hbrBackground    = (HBRUSH)(COLOR_WINDOW);       // window background
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);  // cursor look inside window
    wc.hIcon            = LoadIcon(NULL, IDI_QUESTION); // window icon = question mark
    wc.hInstance        = hInst;                        // window instance = received instance from OS
    wc.lpszClassName    = CLASS_NAME;                   // class name = instance name
    wc.lpfnWndProc      = WindowProc;                   // window procedure = callback to WindowProc

    if (!RegisterClass(&wc)) // register window class - true/false
    {
        MessageBox(NULL, "Unable to RegisterClass", "Login Prompt", NULL);
        return -1;
    }

    CreateWindow(CLASS_NAME, "Login Prompt",        // window class name, window title
                WS_VISIBLE | WS_OVERLAPPEDWINDOW,   // style
                575, 215, 400, 400,                 // x & y origin, window width & height
                NULL, NULL, NULL, NULL              // parent window so set all as null
                );

    MSG msg = {0}; // initialize message obj to 0
    while (GetMessage(&msg, NULL, NULL, NULL)) // event loop
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg); // dispatch message to WindowProc (window procedure)
    }

    UnregisterClass(CLASS_NAME, hInst);
    return (int) msg.wParam;
}

/*
// Setup() - inital setup
*/
void Setup(HINSTANCE hInst)
{
    hInst = hInstance; // Store instance handle in our global variable

    FreeConsole(); // detach process from console (kills console)
    //ShowWindow(GetConsoleWindow(), SW_HIDE); // hide console window
}

/*
// WindowProc() - handles all messages sent from event loop
//
// hWnd - window handler
// msg - message passed from event loop
// wParam - menu item id is passed via wParam
// lParam -
*/
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_CREATE: // message sent when window is initially created
        CreateMenuBar(hWnd);     // setup title bar (menus)
        CreateLoginPrompt(hWnd);  // setup window display (controls)
        break;
    case WM_COMMAND:
        HandleCommandEvents(hWnd, wParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // sends WM_QUIT message via event loop
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam); // default exit value
    }

    return 0;
}

/*
// CreateMenuBar() - create menu bar
//
// Help
//  |
// About
// ----
// Exit
*/
void CreateMenuBar(HWND hWnd)
{
    hMenu = CreateMenu(); // returns empty menu instance
    HMENU hHelpMenu = CreateMenu();

    AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_ABOUT, "About");
    AppendMenu(hHelpMenu, MF_STRING, NULL, NULL);
    AppendMenu(hHelpMenu, MF_STRING, HELP_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "Help");

    SetMenu(hWnd, hMenu); // specify handler to which menu is to be added
}

/*
// CreateLoginPrompt() - create controls (child windows inside parent)
//
// Username: [                ]
// Password: [                ]
// []Remember me       [Submit]
*/
void CreateLoginPrompt(HWND hWnd)
{

    CreateWindow("Static", "Username: ",    // static text, window label
                  WS_VISIBLE | WS_CHILD,    // specify it as a child style
                  75, 200, 125, 25,          // x & y with respect to parent window, child window width & height
                  hWnd, NULL, NULL, NULL    // parent handler
                );

    hEditUsername = CreateWindow("Edit", "",                            // edit box, box text
                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,   // specify it as a child style
                  150, 200, 125, 20,                                     // x & y with respect to parent window, child window width & height
                  hWnd, NULL, NULL, NULL                                // parent handler
                );

    CreateWindow("Static", "Password: ",    // static text, window label
                  WS_VISIBLE | WS_CHILD,    // specify it as a child style
                  75, 230, 125, 25,          // x & y with respect to parent window, child window width & height
                  hWnd, NULL, NULL, NULL    // parent handler
                );

    hEditPassword = CreateWindow("Edit", "",                             // edit box, box text
                  WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,    // child window
                  150, 230, 125, 20,                                      // x & y with respect to parent window, child window width & height
                  hWnd, NULL, NULL, NULL                                 // parent handler
                );

    hButtonSubmit = CreateWindow("Button", "Submit",    // button, button label
                 WS_VISIBLE | WS_CHILD,                 // child window
                 225, 265, 50, 25,                      // x & y with respect to parent window, child window width & height
                 hWnd, NULL, NULL, NULL                 // parent handler
                 );

    hButtonRememberMe = CreateWindow("Button", "Remember me",                           // button, button label
                                     WS_VISIBLE | WS_CHILD | BS_CHECKBOX,               // child window, checkbox
                                     75, 265, 120, 25,                                  // x & y with respect to parent window, child window width & height
                                     hWnd, (HMENU) CHECKBOX_REMEMBER_ME, NULL, NULL     // parent handler
                                     );
}

/*
// HandleCommandEvents() - handle all possible command events
//
// 1. help menu handling
// 2. remember me checkbox handling
*/
void HandleCommandEvents(HWND hWnd, WPARAM wParam)
{
        switch(wParam)
        {
        case HELP_MENU_ABOUT: // handle "about" menu
            // -------------- //
            break;
        case HELP_MENU_EXIT:
            DestroyWindow(hWnd); // sends WM_DESTROY message via event loop
            break;
        case CHECKBOX_REMEMBER_ME:
            if (IsDlgButtonChecked(hWnd, CHECKBOX_REMEMBER_ME))
            {
                CheckDlgButton(hWnd, CHECKBOX_REMEMBER_ME, BST_UNCHECKED);
                isRememberMeChecked = false;
            }
            else
            {
                CheckDlgButton(hWnd, CHECKBOX_REMEMBER_ME, BST_CHECKED);
                isRememberMeChecked = true;
            }
            break;
        }
}

