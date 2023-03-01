#include "stdafx.h"
#include "D3D12Touka.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
	D3D12Touka touka(1920, 1080, L"D3D12 touka");
	WinApplication::Run(&touka, hInstance, nCmdShow);
}

