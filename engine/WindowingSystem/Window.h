#pragma once
#include <Windows.h>

class Window
{
public:
    Window();
    //create
    bool init();
    bool broadcast();
    ~Window();
    //destroy
    bool isRun();
    bool release();

    RECT getClientWindowRect();
    void setHWND(HWND hwnd);

    virtual void onCreate();
    virtual void onUpdate();
    virtual void onDestroy();

protected:
    HWND m_hwnd;
    bool m_is_run;
};
