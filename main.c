#include <windows.h>
#include <stdio.h>

const char g_szClassName[] = "myWindowClass";
int ship_x = 10;
int shot_y = 590;
BOOL shot = FALSE;
BOOL start = FALSE;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_PAINT: {
            PAINTSTRUCT ctx;

            HDC device = BeginPaint(hwnd, &ctx);

            SelectObject(device, GetStockObject(NULL_PEN));

            RECT draw_ship;

            draw_ship.left = ship_x;
            draw_ship.right = ship_x + 50;

            Rectangle(
                    device,
                    draw_ship.left,
                    600,
                    draw_ship.right,
                    650
            );

            RECT draw_turret;

            draw_turret.left = ship_x + 15;
            draw_turret.right = ship_x + 35;

            Rectangle(
                    device,
                    draw_turret.left,
                    590,
                    draw_turret.right,
                    610
            );
            if (shot == TRUE){
                RECT draw_shot;

                draw_shot.left = draw_turret.left;
                draw_shot.top = shot_y;


                Rectangle(
                        device,
                        draw_shot.left,
                        draw_shot.top,
                        draw_shot.left + 20,
                        draw_shot.top + 20
                );
            }
            if (start == TRUE){
                for (int i=0; i < 7; i++){
                    for (int j=0; j < 5; j++){
                        Rectangle(
                                device,
                                i*50 + 20,
                                j*50 + 20,
                                i*50 + 40,
                                j*50 + 40
                                );
                    }
                }
            }


            EndPaint(hwnd, &ctx);

            break;
        }
        case WM_KEYDOWN:
            if (GetAsyncKeyState(VK_LEFT)){
                ship_x = ship_x - 20;
                if (ship_x < -30){
                    ship_x = 450;
                }
                InvalidateRect(hwnd, 0, 1);
            } else if (GetAsyncKeyState(VK_RIGHT)){
                ship_x = ship_x + 20;
                if (ship_x > 450){
                    ship_x = -30;
                }
                InvalidateRect(hwnd, 0, 1);

            } else if (GetAsyncKeyState(VK_SPACE)){
                shot = TRUE;
                InvalidateRect(hwnd, 0, 1);

            } else if(GetAsyncKeyState(0x53)){
                start = TRUE;
                InvalidateRect(hwnd, 0, 1);
            }

            break;
        case WM_TIMER:

            switch(wParam)
            {
                case 0:
                    if (shot == TRUE){
                        shot_y = shot_y - 10;
                        InvalidateRect(hwnd, 0, 1);

                    }
                    if (shot_y < 20){
                        shot_y = 590;
                        shot = FALSE;
                    }
                case 1:
                    if (start == TRUE){

                    }
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

int main()
{

    HMODULE hInstance = GetModuleHandleA(NULL);

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

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
            "QR Invader",
            WS_VISIBLE+WS_OVERLAPPEDWINDOW-WS_THICKFRAME-WS_MAXIMIZEBOX,
            CW_USEDEFAULT, CW_USEDEFAULT, 450, 650,
            NULL, NULL, hInstance, NULL);

    if(hwnd == NULL) //can remove to decrease code size
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!", //can remove to decrease code size
                   MB_ICONEXCLAMATION | MB_OK); //can remove to decrease code size
        return 0; //can remove to decrease code size
    }

    //ShowWindow(hwnd, SW_SHOW);

    SetTimer(hwnd, 0, 15, 0);
    SetTimer(hwnd, 1, 15, 0);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}