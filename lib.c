#include <windows.h>
#include <stdio.h>

typedef void (*custom_callback)(int cod);
custom_callback global_callback;

LRESULT CALLBACK proc(int code, WPARAM w, LPARAM l)
{
    if (code >= 0)
    {
        KBDLLHOOKSTRUCT *k = (KBDLLHOOKSTRUCT* ) l;

        global_callback(k->vkCode);
    }

    return CallNextHookEx(NULL, code, w, l);
}

void run(custom_callback cfn)
{
    global_callback = cfn;

    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, proc, NULL, 0);
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
}