#pragma once
#include "DXHelper.h"
#include "WinApplication.h"

using Microsoft::WRL::ComPtr;

class D3D12Touka
{
public:
	D3D12Touka(UINT width, UINT height, std::wstring name);

    virtual void OnInit();
    //virtual void OnUpdate();
    //virtual void OnRender();
    //virtual void OnDestroy();

    
    void LoadPipeline();
    //void LoadAssets();
    //void PopulateCommandList();
    //void WaitForPreviousFrame();

    // アクセサ
    UINT GetWidth() const { return m_width; }
    UINT GetHeight() const { return m_height; }
    const WCHAR* GetTitle() const { return m_title.c_str(); }

    void GetHardwareAdapter(
        IDXGIFactory1* pFactory, // ファクトリ
        IDXGIAdapter1** ppAdapter, // アダプターへのポインタ
        bool requestHighPerformanceAdapter = false);

protected:
    UINT m_width;
    UINT m_height;

private:
    static const UINT FrameCount = 2; // スワップチェーンの枚数
    
    std::wstring m_title; // ウィンドウタイトル

    // Pipeline objects.
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<IDXGISwapChain3> m_swapChain;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    UINT m_rtvDescriptorSize;

    UINT m_frameIndex; // バックバッファのインデックス



    ComPtr<ID3D12CommandQueue> m_commandQueue;

};