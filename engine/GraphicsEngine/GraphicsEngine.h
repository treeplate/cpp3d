#pragma once
#include <d3d11.h>

class SwapChain;
class DeviceContext;
class VertexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;

class GraphicsEngine
{
public:
    GraphicsEngine();
    bool init();
    bool release();
    ~GraphicsEngine();

public:
    SwapChain *createSwapChain();
    DeviceContext *getImmediateDeviceContext();
    VertexBuffer *createVertexBuffer();
    ConstantBuffer *createConstantBuffer();
    bool compileVertexShader(const wchar_t *file_name, const char *entry_point, void **shader_byte_code, size_t *byte_code_size);
    bool compilePixelShader(const wchar_t *file_name, const char *entry_point, void **shader_byte_code, size_t *byte_code_size);
    VertexShader *createVertexShader(const void *shader_byte_code, size_t byte_code_size);
    PixelShader *createPixelShader(const void *shader_byte_code, size_t byte_code_size);
    void releaseCompiledShader();

public:
    static GraphicsEngine *get();

private:
    ID3D11Device *m_d3d_device;
    D3D_FEATURE_LEVEL m_feature_level;
    DeviceContext *m_imm_device_context;

private:
    IDXGIDevice *m_dxgi_device;
    ID3D11DeviceContext *m_imm_context;
    IDXGIAdapter *m_dxgi_adapter;
    IDXGIFactory *m_dxgi_factory;
    ID3DBlob *m_blob = nullptr;

    ID3DBlob *m_vsblob;
    ID3DBlob *m_psblob;
    ID3D11VertexShader *m_vs;
    ID3D11PixelShader *m_ps;

private:
    friend class SwapChain;
    friend class VertexBuffer;
    friend class VertexShader;
    friend class PixelShader;
    friend class ConstantBuffer;
};