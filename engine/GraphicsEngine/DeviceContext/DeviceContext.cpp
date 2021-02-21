#include "DeviceContext.h"
#include <d3dcompiler.h>
#include "../SwapChain/SwapChain.h"
#include "../VertexBuffer/VertexBuffer.h"
#include "../ConstantBuffer/ConstantBuffer.h"
#include "../VertexShader/VertexShader.h"
#include "../PixelShader/PixelShader.h"
DeviceContext::DeviceContext(ID3D11DeviceContext *device_context)
{
    m_device_context = device_context;
}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::release()
{
    m_device_context->Release();
    delete this;
}

void DeviceContext::setVertexShader(VertexShader *vertex_shader)
{
    m_device_context->VSSetShader(vertex_shader->m_vs, nullptr, 0);
}

void DeviceContext::setPixelShader(PixelShader *pixel_shader)
{
    m_device_context->PSSetShader(pixel_shader->m_ps, nullptr, 0);
}

void DeviceContext::setVertexBuffer(VertexBuffer *vertex_buffer)
{
    UINT stride = vertex_buffer->m_size_vertex;
    UINT offset = 0;
    m_device_context->IASetVertexBuffers(0, 1, &vertex_buffer->m_buffer, &stride, &offset);
    m_device_context->IASetInputLayout(vertex_buffer->m_layout);
}

void DeviceContext::drawTriangleStrip(UINT vertex_count, UINT start_vertex_index)
{
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::clearRenderTargetColor(SwapChain *swap_chain, float r, float g, float b, float a)
{
    FLOAT clear_color[] = {
        r,
        g,
        b,
        a};
    m_device_context->ClearRenderTargetView(swap_chain->m_rtv, clear_color);
    m_device_context->OMSetRenderTargets(1, &swap_chain->m_rtv, NULL);
}

void DeviceContext::drawTriangleList(UINT vertex_count, UINT start_vertex_index)
{
    m_device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    m_device_context->Draw(vertex_count, start_vertex_index);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
    D3D11_VIEWPORT vp = {};
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_device_context->RSSetViewports(1, &vp);
}
void DeviceContext::setConstantBuffer(PixelShader *pixel_shader, ConstantBuffer *buffer)
{
    m_device_context->VSSetConstantBuffers(0, 1, &buffer->m_buffer);
}
void DeviceContext::setConstantBuffer(VertexShader *vertex_shader, ConstantBuffer *buffer)
{
    m_device_context->PSSetConstantBuffers(0, 1, &buffer->m_buffer);
}