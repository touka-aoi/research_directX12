#pragma once

class WinApplication
{
public:
    static int Run(HINSTANCE hInstance, int nCmdShow); // �J�n�֐�
    static HWND GetHwnd() { return m_hwnd; } // �A�N�Z�T

protected:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam); // �E�B���h�E�v���V�[�W��

private:
    static HWND m_hwnd;
};
