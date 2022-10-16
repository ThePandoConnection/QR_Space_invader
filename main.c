#include <windows.h>
#include <stdio.h>

const char g_szClassName[] = "myWindowClass";
int shooter_x = 10;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_PAINT:{
            PAINTSTRUCT ctx;

            HDC device = BeginPaint(hwnd, &ctx);

            SelectObject(device, GetStockObject(NULL_PEN));

            RECT draw_rect;

            draw_rect.left = shooter_x;
            draw_rect.right = shooter_x +50;

            Rectangle(
                    device,
                    draw_rect.left,
                    600,
                    draw_rect.right,
                    650
                    );

            EndPaint(hwnd, &ctx);
            break;
        }
        case WM_KEYDOWN:
            if (GetAsyncKeyState(VK_LEFT)){
                shooter_x = shooter_x - 20;
                if (shooter_x < 0){
                    shooter_x = 450;
                }
                InvalidateRect(hwnd, 0, 1);
            } else if (GetAsyncKeyState(VK_RIGHT)){
                shooter_x = shooter_x + 20;
                if (shooter_x > 450){
                    shooter_x = 0;
                }
                InvalidateRect(hwnd, 0, 1);
            } else if (GetAsyncKeyState(VK_SPACE)){

            }

            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!", //can remove to decrease code size
                   MB_ICONEXCLAMATION | MB_OK); //can remove to decrease code size
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
            WS_EX_CLIENTEDGE,
            g_szClassName,
            "Space Invader",
            WS_VISIBLE+WS_OVERLAPPEDWINDOW-WS_THICKFRAME-WS_MAXIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, 450, 650,
            NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) //can remove to decrease code size
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", //can remove to decrease code size
                   MB_ICONEXCLAMATION | MB_OK); //can remove to decrease code size
        return 0; //can remove to decrease code size
    }

    ShowWindow(hwnd, nCmdShow);


    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}