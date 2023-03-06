#pragma once

struct Vertex
{
	DirectX::XMFLOAT3 position;
};

struct Mesh
{
	// 頂点データ
	std::vector<Vertex> Vertices;

	std::vector<unsigned short> Indices;

	// リソース
	D3D12_VERTEX_BUFFER_VIEW VBView;
	D3D12_INDEX_BUFFER_VIEW IBView;

	Microsoft::WRL::ComPtr<ID3D12Resource> VertexResources;
	Microsoft::WRL::ComPtr<ID3D12Resource> IndexResource;
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