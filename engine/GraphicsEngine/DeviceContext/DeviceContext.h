#pragma once
#include <d3d11.h>

class SwapChain;
class VertexBuffer;
class VertexShader;
class PixelShader;
class ConstantBuffer;

class DeviceContext
{
private:
    ID3D11DeviceContext *m_device_context;

public:
    DeviceContext(ID3D11DeviceContext *device_context);
    ~DeviceContext();
    void release();
    void drawTriangleList(UINT vertex_count, UINT start_vertex_index);
    void drawTriangleStrip(UINT vertex_count, UINT start_vertex_index);
    void setVertexBuffer(VertexBuffer *vertex_buffer);
    void setViewportSize(UINT width, UINT height);
    void setVertexShader(VertexShader *vertex_shader);
    void setPixelShader(PixelShader *pixel_shader);
    void clearRenderTargetColor(SwapChain *swap_chain, float r, float g, float b, float a);
    void setConstantBuffer(PixelShader *pixel_shader, ConstantBuffer *constant_buffer);
    void setConstantBuffer(VertexShader *vertex_shader, ConstantBuffer *constant_buffer);

private:
    friend class ConstantBuffer;
};