#include "stdafx.h"
#include "DXHelper.h"
#include "Model.h"

using namespace DirectX;
using namespace Microsoft::WRL;

namespace
{
	const D3D12_INPUT_ELEMENT_DESC  c_elementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
	};

}

HRESULT Model::LoadModel()
{
	std::vector<Vertex> triangleVertices =
	{
		{ { 0.25f, 0.25f, 0.0f } },
		{ { 0.25f, -0.25f, 0.0f } },
		{ { -0.25f, 0.25f, 0.0f }},
		{ { -0.25f, -0.25f, 0.0f }}
	};

	m_meshes.Vertices = triangleVertices;

	std::vector<unsigned short>  rectangleIndices =
	{
		0, 1, 2,
		2, 1, 3
	};

	m_meshes.Indices = rectangleIndices;

	return S_OK;
}


HRESULT Model::UploadGpuResources(ID3D12Device* device, ID3D12CommandQueue* cmdQueue, ID3D12CommandAllocator* cmdAlloc, ID3D12GraphicsCommandList* cmdList)
{
	// クラスGPUリソースの初期化
	
	CD3DX12_RESOURCE_DESC vertexDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(Vertex) * m_meshes.Vertices.size());
	CD3DX12_RESOURCE_DESC indexDesc = CD3DX12_RESOURCE_DESC::Buffer(sizeof(unsigned short) * m_meshes.Indices.size());
		

	CD3DX12_HEAP_PROPERTIES defaultHeap = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_DEFAULT);

	ThrowIfFailed(device->CreateCommittedResource(&defaultHeap, D3D12_HEAP_FLAG_NONE, &vertexDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_meshes.VertexResources)));
	ThrowIfFailed(device->CreateCommittedResource(&defaultHeap, D3D12_HEAP_FLAG_NONE, &indexDesc, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_meshes.IndexResource)));
		

	// GPUリソース
	ComPtr<ID3D12Resource> vertexUpload;
	ComPtr<ID3D12Resource> indexUpload;
	// 頂点読み込み
	

	// GPUアップロード
	CD3DX12_HEAP_PROPERTIES uploadHeap = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	ThrowIfFailed(device->CreateCommittedResource(&uploadHeap, D3D12_HEAP_FLAG_NONE, &vertexDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&vertexUpload)));
	ThrowIfFailed(device->CreateCommittedResource(&uploadHeap, D3D12_HEAP_FLAG_NONE, &indexDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&indexUpload)));

	{
		UINT8* pVertexDataBegin;
		CD3DX12_RANGE readRange(0, 0);
		ThrowIfFailed(vertexUpload->Map(0, &readRange, reinterpret_cast<void**>(&pVertexDataBegin)));
		memcpy(pVertexDataBegin, m_meshes.Vertices.data(), sizeof(Vertex) * m_meshes.Vertices.size());
		vertexUpload->Unmap(0, nullptr);
	}

	{
		UINT8* memory = nullptr;
		ThrowIfFailed(indexUpload->Map(0, nullptr, reinterpret_cast<void**>(&memory)));
		memcpy(memory, m_meshes.Indices.data(), sizeof(unsigned short) * m_meshes.Indices.size());
		indexUpload->Unmap(0, nullptr);
	}

	// インデックスビューの初期化
	m_meshes.IBView.BufferLocation = m_meshes.IndexResource->GetGPUVirtualAddress();
	m_meshes.IBView.Format = DXGI_FORMAT_R16_UINT;
	m_meshes.IBView.SizeInBytes = sizeof(unsigned short) * m_meshes.Indices.size();

	// 頂点ビューの初期化
	m_meshes.VBView.BufferLocation = m_meshes.VertexResources->GetGPUVirtualAddress();
	m_meshes.VBView.StrideInBytes = sizeof(Vertex);
	m_meshes.VBView.SizeInBytes = sizeof(Vertex) * m_meshes.Vertices.size();

	// コマンドリストの実行
	cmdList->Reset(cmdAlloc, nullptr);

	auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_meshes.VertexResources.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
	cmdList->CopyResource(m_meshes.VertexResources.Get(), vertexUpload.Get());
	barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_meshes.VertexResources.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	cmdList->ResourceBarrier(1, &barrier);

	barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_meshes.IndexResource.Get(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
	cmdList->CopyResource(m_meshes.IndexResource.Get(), indexUpload.Get());
	barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_meshes.IndexResource.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
	cmdList->ResourceBarrier(1, &barrier);

	ThrowIfFailed(cmdList->Close());
	ID3D12CommandList* ppCommandLists[] = { cmdList };
	cmdQueue->ExecuteCommandLists(1, ppCommandLists);

	// フェンスの作成
	ComPtr<ID3D12Fence> fence;
	ThrowIfFailed(device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence)));

	cmdQueue->Signal(fence.Get(), 1);

	// GPUを待機
	if (fence->GetCompletedValue() != 1)
	{
		HANDLE event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		fence->SetEventOnCompletion(1, event);

		WaitForSingleObjectEx(event, INFINITE, false);
		CloseHandle(event);
	}

	return S_OK;

}
