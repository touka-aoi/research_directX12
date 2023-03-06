#pragma once

class Texture
{
public:
	//HRESULT LoadFromFile(const wchar_t* filename);
	HRESULT LoadGenerateTexture();
	HRESULT UploadGpuResources(ID3D12Device* device, ID3D12CommandQueue* cmdQueue, ID3D12CommandAllocator* cmdAlloc, ID3D12GraphicsCommandList* cmdList);
	std::vector<UINT8> texture;
private:
};