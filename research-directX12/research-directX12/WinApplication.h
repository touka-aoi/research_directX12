#pragma once

class WinApplication
{
public:
    static int Run(HINSTANCE hInstance, int nCmdShow); // 開始関数
    static HWND GetHwnd() { return m_hwnd; } // アクセサ

protected:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // ウィンドウプロシージャ

private:
    static HWND m_hwnd;
};
