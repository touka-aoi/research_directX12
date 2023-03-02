#pragma once
#include "DXHelper.h"
#include "WinApplication.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

class D3D12Touka
{
public:
	D3D12Touka(UINT width, UINT height, std::wstring name);

    virtual void OnInit();
    virtual void OnRender();
    virtual void OnUpdate();
    //virtual void OnDestroy();

    
    void LoadPipeline();
    void PopulateCommandList();
    void LoadAssets();
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
    float m_aspectRatio;

    std::wstring GetAssetFullPath(LPCWSTR assetName);

private:
    static const UINT FrameCount = 2; // スワップチェーンの枚数
    
    std::wstring m_title; // ウィンドウタイトル

    struct Vertex
    {
        XMFLOAT3 position;
        //XMFLOAT4 color;
    };

    // Pipeline objects.
    CD3DX12_VIEWPORT m_viewport;
    CD3DX12_RECT m_scissorRect;
    ComPtr<ID3D12Device> m_device;
    ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
    ComPtr<ID3D12CommandAllocator> m_commandAllocator;
    ComPtr<IDXGISwapChain3> m_swapChain;
    ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
    ComPtr<ID3D12GraphicsCommandList> m_commandList;
    ComPtr<ID3D12RootSignature> m_rootSignature;
    ComPtr<ID3D12PipelineState> m_pipelineState;
    UINT m_rtvDescriptorSize;

    // Application Resource
    ComPtr<ID3D12Resource> m_vertexBuffer;
    D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;


    // 同期オブジェクト
    UINT m_frameIndex; // バックバッファのインデックス
    UINT64 m_fenceValue; // フェンスの値
    ComPtr<ID3D12Fence> m_fence; // フェンス
    HANDLE m_fenceEvent; // フェンスイベント
    D3D12_RESOURCE_BARRIER m_resourceBarrier; // リソースバリア


    ComPtr<ID3D12CommandQueue> m_commandQueue;

    std::wstring m_assetsPath;

    void WaitForPreviousFrame();
};