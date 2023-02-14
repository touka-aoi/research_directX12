#pragma once
#include "DXHelper.h"

using Microsoft::WRL::ComPtr;

class D3D12Touka
{
public:
	D3D12Touka(UINT width, UINT height, std::wstring name);

    virtual void OnInit();
    //virtual void OnUpdate();
    //virtual void OnRender();
    //virtual void OnDestroy();

    // Pipeline objects.
    ComPtr<ID3D12Device> m_device;

    void LoadPipeline();
    //void LoadAssets();
    //void PopulateCommandList();
    //void WaitForPreviousFrame();

    void GetHardwareAdapter(
        IDXGIFactory1* pFactory, // ファクトリ
        IDXGIAdapter1** ppAdapter, // アダプターへのポインタ
        bool requestHighPerformanceAdapter = false);
};