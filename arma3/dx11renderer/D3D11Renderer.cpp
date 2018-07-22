#include "D3D11Renderer.h"

D3D11Renderer::D3D11Renderer(IDXGISwapChain *SwapChain)
{
	this->device = NULL;
	this->deviceContext = NULL;
	this->mVS = NULL;
	this->mPS = NULL;
	this->transparency = NULL;
	this->mInputLayout = NULL;
	this->mVertexBuffer = NULL;

	this->swapChain = SwapChain;

	this->stateSaver = new D3D11StateSaver();
}

D3D11Renderer::~D3D11Renderer()
{
	SAFE_DELETE(this->fontfactory);
	SAFE_DELETE(this->fontwrapper);
	SAFE_DELETE(this->stateSaver);
	SAFE_RELEASE(this->mVS);
	SAFE_RELEASE(this->mPS);
	SAFE_RELEASE(this->transparency);
	SAFE_RELEASE(this->mInputLayout);
	SAFE_RELEASE(this->mVertexBuffer);
	SAFE_RELEASE(this->swapChain);
	SAFE_RELEASE(this->device);
	SAFE_RELEASE(this->deviceContext);
}

bool D3D11Renderer::Initialize()
{
	HRESULT hr;

	if (!this->swapChain)
		return false;

	this->swapChain->GetDevice(__uuidof(this->device), (void**)&this->device);
	if (!this->device)
		return false;

	this->device->GetImmediateContext(&this->deviceContext);
	if (!this->deviceContext)
		return false;

	hr = FW1CreateFactory(FW1_VERSION, &this->fontfactory);
	if (FAILED(hr))
		return false;

	hr = fontfactory->CreateFontWrapper(device, L"Arial", &this->fontwrapper);
	if (FAILED(hr))
		return false;
	
	typedef HRESULT(__stdcall* D3DCompile_t)(LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName, const D3D_SHADER_MACRO *pDefines, ID3DInclude *pInclude, LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2, ID3DBlob **ppCode, ID3DBlob *ppErrorMsgs);
	D3DCompile_t myD3DCompile = (D3DCompile_t)GetProcAddress(GetD3DCompiler(), "D3DCompile");
	if (!myD3DCompile)
		return false;

	ID3D10Blob *VS, *PS;
	hr = myD3DCompile(D3D11FillShader, sizeof(D3D11FillShader), NULL, NULL, NULL, "VS", "vs_4_0", 0, 0, &VS, NULL);
	if (FAILED(hr))
		return false;

	hr = this->device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &this->mVS);
	if (FAILED(hr))
	{
		SAFE_RELEASE(VS);
		return false;
	}
				
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = this->device->CreateInputLayout(layout, ARRAYSIZE(layout), VS->GetBufferPointer(), VS->GetBufferSize(), &this->mInputLayout);
	SAFE_RELEASE(VS);
	if (FAILED(hr))
		return false;
		
	myD3DCompile(D3D11FillShader, sizeof(D3D11FillShader), NULL, NULL, NULL, "PS", "ps_4_0", 0, 0, &PS, NULL);
	if (FAILED(hr))
		return false;

	hr = this->device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &this->mPS);
	if (FAILED(hr))
	{
		SAFE_RELEASE(PS);
		return false;
	}

	D3D11_BUFFER_DESC bufferDesc;

	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = 4 * sizeof(COLOR_VERTEX);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;

	hr = this->device->CreateBuffer(&bufferDesc, NULL, &this->mVertexBuffer);
	if(FAILED(hr))
		return false;

	D3D11_BLEND_DESC blendStateDescription;
	ZeroMemory(&blendStateDescription, sizeof(blendStateDescription));

	blendStateDescription.RenderTarget[0].BlendEnable = TRUE;
	blendStateDescription.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendStateDescription.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendStateDescription.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendStateDescription.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendStateDescription.RenderTarget[0].RenderTargetWriteMask = 0x0f;

	hr = this->device->CreateBlendState(&blendStateDescription, &this->transparency);
	if (FAILED(hr))
		return false;

	return true;
}

void D3D11Renderer::FillRect(float x, float y, float w, float h, Color color)
{
	if (this->deviceContext == NULL)
		return;

	int a = color.A & 0xff;
	int r = color.R & 0xff;
	int g = color.G & 0xff;
	int b = color.B & 0xff;

	UINT viewportNumber = 1;

	D3D11_VIEWPORT vp;

	this->deviceContext->RSGetViewports(&viewportNumber, &vp);

	float x0 = x;
	float y0 = y;
	float x1 = x + w;
	float y1 = y + h;

	float xx0 = 2.0f * (x0 - 0.5f) / vp.Width - 1.0f;
	float yy0 = 1.0f - 2.0f * (y0 - 0.5f) / vp.Height;
	float xx1 = 2.0f * (x1 - 0.5f) / vp.Width - 1.0f;
	float yy1 = 1.0f - 2.0f * (y1 - 0.5f) / vp.Height;

	COLOR_VERTEX* v = NULL;
	D3D11_MAPPED_SUBRESOURCE mapData;

	if (FAILED(this->deviceContext->Map(this->mVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapData)))
		return;

	v = (COLOR_VERTEX*)mapData.pData;

	v[0].Position.x = (float)x0;
	v[0].Position.y = (float)y0;
	v[0].Position.z = 0;
	v[0].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	v[1].Position.x = (float)x1;
	v[1].Position.y = (float)y1;
	v[1].Position.z = 0;
	v[1].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	v[0].Position.x = xx0;
	v[0].Position.y = yy0;
	v[0].Position.z = 0;
	v[0].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	v[1].Position.x = xx1;
	v[1].Position.y = yy0;
	v[1].Position.z = 0;
	v[1].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	v[2].Position.x = xx0;
	v[2].Position.y = yy1;
	v[2].Position.z = 0;
	v[2].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	v[3].Position.x = xx1;
	v[3].Position.y = yy1;
	v[3].Position.z = 0;
	v[3].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));


	this->deviceContext->Unmap(this->mVertexBuffer, NULL);

	UINT Stride = sizeof(COLOR_VERTEX);
	UINT Offset = 0;

	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	this->deviceContext->OMSetBlendState(this->transparency, blendFactor, 0xffffffff);

	this->deviceContext->IASetVertexBuffers(0, 1, &this->mVertexBuffer, &Stride, &Offset);
	this->deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	this->deviceContext->IASetInputLayout(this->mInputLayout);

	this->deviceContext->VSSetShader(this->mVS, 0, 0);
	this->deviceContext->PSSetShader(this->mPS, 0, 0);
	this->deviceContext->GSSetShader(NULL, 0, 0);
	this->deviceContext->Draw(4, 0);
}

void D3D11Renderer::DrawLine(float x1, float y1, float x2, float y2, Color color)
{
	if (this->deviceContext == NULL)
		return;

	int a = color.A & 0xff;
	int r = color.R & 0xff;
	int g = color.G & 0xff;
	int b = color.B & 0xff;

	UINT viewportNumber = 1;

	D3D11_VIEWPORT vp;

	this->deviceContext->RSGetViewports(&viewportNumber, &vp);
		
	float xx0 = 2.0f * (x1 - 0.5f) / vp.Width - 1.0f;
	float yy0 = 1.0f - 2.0f * (y1 - 0.5f) / vp.Height;
	float xx1 = 2.0f * (x2 - 0.5f) / vp.Width - 1.0f;
	float yy1 = 1.0f - 2.0f * (y2 - 0.5f) / vp.Height;

	COLOR_VERTEX* v = NULL;

	D3D11_MAPPED_SUBRESOURCE mapData;

	if (FAILED(this->deviceContext->Map(this->mVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &mapData)))
		return;

	v = (COLOR_VERTEX*)mapData.pData;

	v[0].Position.x = xx0;
	v[0].Position.y = yy0;

	v[0].Position.z = 0;
	v[0].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	v[1].Position.x = xx1;
	v[1].Position.y = yy1;
	v[1].Position.z = 0;
	v[1].Color = D3DXCOLOR(
		((float)r / 255.0f),
		((float)g / 255.0f),
		((float)b / 255.0f),
		((float)a / 255.0f));

	this->deviceContext->Unmap(this->mVertexBuffer, NULL);

	UINT Stride = sizeof(COLOR_VERTEX);
	UINT Offset = 0;

	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	this->deviceContext->OMSetBlendState(this->transparency, blendFactor, 0xffffffff);

	this->deviceContext->IASetVertexBuffers(0, 1, &this->mVertexBuffer, &Stride, &Offset);
	this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
	this->deviceContext->IASetInputLayout(this->mInputLayout);

	this->deviceContext->VSSetShader(this->mVS, 0, 0);
	this->deviceContext->PSSetShader(this->mPS, 0, 0);
	this->deviceContext->GSSetShader(NULL, 0, 0);
	this->deviceContext->Draw(2, 0);
}

void D3D11Renderer::DrawString(int size, int x, int y, Color color, std::string text, bool outline)
{
	std::wstring wtext(text.begin(), text.end());

	if (outline)
	{
		DWORD black = (DWORD)((((color.A) & 0xff) << 24) | (((0) & 0xff) << 16) | (((0) & 0xff) << 8) | ((0) & 0xff));
		fontwrapper->DrawString(this->deviceContext, wtext.c_str(), size, x - 1, y, black, FW1_RESTORESTATE | FW1_ALIASED);
		fontwrapper->DrawString(this->deviceContext, wtext.c_str(), size, x, y - 1, black, FW1_RESTORESTATE | FW1_ALIASED);
		fontwrapper->DrawString(this->deviceContext, wtext.c_str(), size, x + 1, y, black, FW1_RESTORESTATE | FW1_ALIASED);
		fontwrapper->DrawString(this->deviceContext, wtext.c_str(), size, x, y + 1, black, FW1_RESTORESTATE | FW1_ALIASED);
	}

	DWORD clr = (DWORD)((((color.A) & 0xff) << 24) | (((color.B) & 0xff) << 16) | (((color.G) & 0xff) << 8) | ((color.R) & 0xff));
	fontwrapper->DrawString(this->deviceContext, wtext.c_str(), size, x, y, clr, FW1_RESTORESTATE | FW1_ALIASED);
}

float D3D11Renderer::GetWidth()
{
	D3D11_VIEWPORT vp;
	UINT nvp = 1;
	this->deviceContext->RSGetViewports(&nvp, &vp);
	return vp.Width;
}

float D3D11Renderer::GetHeight()
{
	D3D11_VIEWPORT vp;
	UINT nvp = 1;
	this->deviceContext->RSGetViewports(&nvp, &vp);
	return vp.Height;
}

void D3D11Renderer::BeginScene()
{
	this->restoreState = false;
	if (SUCCEEDED(this->stateSaver->saveCurrentState(this->deviceContext)))
		this->restoreState = true;

	float blendFactor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
	this->deviceContext->OMSetBlendState(this->transparency, blendFactor, 0xffffffff);
	this->deviceContext->IASetInputLayout(this->mInputLayout);
}

void D3D11Renderer::EndScene()
{
	if (this->restoreState)
		this->stateSaver->restoreSavedState();
}