#include "GraphicsEngine.h"
#include "SwapChain\SwapChain.h"
#include "DeviceContext\DeviceContext.h"
#include "VertexBuffer\VertexBuffer.h"
#include "ConstantBuffer\ConstantBuffer.h"
#include "VertexShader\VertexShader.h"
#include "PixelShader\PixelShader.h"
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

GraphicsEngine::GraphicsEngine()
{
}

GraphicsEngine::~GraphicsEngine()
{
}

VertexShader *GraphicsEngine::createVertexShader(const void *shader_byte_code, size_t byte_code_size)
{
    VertexShader *vs = new VertexShader();
    if (!vs->init(shader_byte_code, byte_code_size))
    {
        vs->release();
        return nullptr;
    }
    return vs;
}

PixelShader *GraphicsEngine::createPixelShader(const void *shader_byte_code, size_t byte_code_size)
{
    PixelShader *ps = new PixelShader();
    if (!ps->init(shader_byte_code, byte_code_size))
    {
        ps->release();
        return nullptr;
    }
    return ps;
}

void GraphicsEngine::releaseCompiledShader()
{
    if (m_blob)
        m_blob->Release();
}

bool GraphicsEngine::compileVertexShader(const wchar_t *file_name, const char *entry_point, void **shader_byte_code, size_t *byte_code_size)
{
    ID3DBlob *error_blob = nullptr;
    HRESULT hr = ::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point, "vs_5_0", 0, 0, &m_blob, &error_blob);
    if (FAILED(hr))
    {
        if (error_blob)
            error_blob->Release();
        return false;
    }
    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();
    return true;
}

bool GraphicsEngine::compilePixelShader(const wchar_t *file_name, const char *entry_point, void **shader_byte_code, size_t *byte_code_size)
{
    ID3DBlob *error_blob = nullptr;
    HRESULT hr = ::D3DCompileFromFile(file_name, nullptr, nullptr, entry_point, "ps_5_0", 0, 0, &m_blob, &error_blob);
    if (FAILED(hr))
    {
        if (error_blob)
            error_blob->Release();
        return false;
    }
    *shader_byte_code = m_blob->GetBufferPointer();
    *byte_code_size = m_blob->GetBufferSize();
    return true;
}

bool GraphicsEngine::init()
{
    D3D_DRIVER_TYPE driver_types[] = {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE};
    UINT num_driver_types = ARRAYSIZE(driver_types);

    D3D_FEATURE_LEVEL feature_levels[] = {
        D3D_FEATURE_LEVEL_11_0};

    UINT num_feature_levels = ARRAYSIZE(feature_levels);
    HRESULT res = 0;
    for (UINT driver_type_index = 0; driver_type_index < num_driver_types; driver_type_index++)
    {
        HRESULT res = D3D11CreateDevice(NULL, driver_types[driver_type_index], NULL, NULL, feature_levels, num_feature_levels, D3D11_SDK_VERSION, &m_d3d_device, &m_feature_level, &m_imm_context);
        if (SUCCEEDED(res))
        {
            break;
        }
    }
    if (FAILED(res))
    {
        return false;
    }
    m_imm_device_context = new DeviceContext(m_imm_context);
    m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), (void **)&m_dxgi_device);
    m_dxgi_device->GetParent(_uuidof(IDXGIAdapter), (void **)&m_dxgi_adapter);
    m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), (void **)&m_dxgi_factory);
    return true;
}

SwapChain *GraphicsEngine::createSwapChain()
{
    return new SwapChain();
}

bool GraphicsEngine::release()
{
    m_d3d_device->Release();
    m_dxgi_device->Release();
    m_dxgi_adapter->Release();
    m_dxgi_factory->Release();
    m_imm_device_context->release();

    return true;
}

DeviceContext *GraphicsEngine::getImmediateDeviceContext()
{
    return this->m_imm_device_context;
}

VertexBuffer *GraphicsEngine::createVertexBuffer()
{
    return new VertexBuffer();
}

ConstantBuffer *GraphicsEngine::createConstantBuffer()
{
    return new ConstantBuffer();
}

GraphicsEngine *GraphicsEngine::get()
{
    static GraphicsEngine engine;
    return &engine;
}