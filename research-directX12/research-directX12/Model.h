#pragma once

struct Vertex
{
	DirectX::XMFLOAT3 position;
};

struct Mesh
{
	std::vector<Vertex> Vertices;

	// ÉäÉ\Å[ÉX
	D3D12_VERTEX_BUFFER_VIEW VBView;
	Microsoft::WRL::ComPtr<ID3D12Resource> VertexResources;
};

class Model
{
public: 
	//HRESULT LoadFromFile(const wchar_t* filename);
	HRESULT LoadModel();
	HRESULT UploadGpuResources(ID3D12Device* device, ID3D12CommandQueue* cmdQueue, ID3D12CommandAllocator* cmdAlloc, ID3D12GraphicsCommandList* cmdList);
	Mesh m_meshes;
private:
};