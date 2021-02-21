#include "SwapChain.h"
#include "../GraphicsEngine.h"

SwapChain::SwapChain() {}
SwapChain::~SwapChain() {}
bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
    DXGI_SWAP_CHAIN_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.BufferCount = 1;
    desc.BufferDesc.Width = width;
    desc.BufferDesc.Height = height;
    desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.BufferDesc.RefreshRate.Numerator = 60;
    desc.BufferDesc.RefreshRate.Denominator = 1;
    desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    desc.OutputWindow = hwnd;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Windowed = TRUE;
    ID3D11Device *device = GraphicsEngine::get()->m_d3d_device;
    HRESULT hr = GraphicsEngine::get()->m_dxgi_factory->CreateSwapChain(device, &desc, &m_swap_chain);
    if (FAILED(hr))
    {
        return false;
    }
    ID3D11Texture2D *buffer = NULL;
    hr = m_swap_chain->GetBuffer(0, _uuidof(ID3D11Texture2D), (void **)&buffer);
    if (FAILED(hr))
    {
        return false;
    }
    hr = device->CreateRenderTargetView(buffer, NULL, &m_rtv);
    if (FAILED(hr))
    {
        return false;
    }
    buffer->Release();
    return true;
}
bool SwapChain::present(bool vsync)
{
    if (FAILED(m_swap_chain->Present(vsync, NULL)))
    {
        return false;
    }
    return true;
}
bool SwapChain::release()
{
    m_swap_chain->Release();
    delete this;
    return true;
}