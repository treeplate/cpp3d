#pragma once
#include "..\engine\WindowingSystem\Window.h"
#include "..\engine\GraphicsEngine\GraphicsEngine.h"
#include "..\engine\GraphicsEngine\SwapChain\SwapChain.h"
#include "..\engine\GraphicsEngine\DeviceContext\DeviceContext.h"
#include "..\engine\GraphicsEngine\VertexBuffer\VertexBuffer.h"
#include "..\engine\GraphicsEngine\VertexShader\VertexShader.h"
#include "..\engine\GraphicsEngine\PixelShader\PixelShader.h"
#include "..\engine\GraphicsEngine\ConstantBuffer\ConstantBuffer.h"
class AppWindow : public Window
{
public:
    AppWindow();

    void updateQuadPosition();

    ~AppWindow();

protected:
    void onCreate();
    void onUpdate();
    void onDestroy();

private:
    SwapChain *m_swap_chain;
    VertexBuffer *m_vb;
    VertexShader *m_vs;
    PixelShader *m_ps;
    ConstantBuffer *m_cb;
};