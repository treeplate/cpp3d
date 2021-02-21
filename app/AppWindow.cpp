#include "AppWindow.h"
#include <Windows.h>
#include "../engine/Math/Vector3D.h"
#include "../engine/Math/Matrix4x4.h"

struct vertex
{
    Vector3D position;
    Vector3D endPosition;
    Vector3D color;
    Vector3D endColor;
};
__declspec(align(16)) struct constant
{
    Matrix4x4 m_world;
    Matrix4x4 m_view;
    Matrix4x4 m_proj;
    unsigned int m_time;
};

AppWindow::AppWindow()
{
}

void AppWindow::onCreate()
{
    Window::onCreate();
    GraphicsEngine::get()->init();

    m_swap_chain = GraphicsEngine::get()->createSwapChain();
    RECT rc = this->getClientWindowRect();
    // TODO(elih): check if the following line returns true
    m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
    vertex list[] = {
        {
            Vector3D(-0.5f, -0.5f, 0.0f),
            Vector3D(0.0f, -0.5f, 0.0f),
            Vector3D(1, 0, 0),
            Vector3D(1, 1, 0),
        }, // POS1
        {
            Vector3D(-0.5f, 0.5f, 0.0f),
            Vector3D(0.0f, 0.5f, 0.0f),
            Vector3D(1, 1, 0),
            Vector3D(0, 0, 1),
        }, // POS2
        {
            Vector3D(0.5f, -0.5f, 0.0f),
            Vector3D(1.0f, -0.5f, 0.0f),
            Vector3D(1, 1, 1),
            Vector3D(1, 0, 0),
        }, // POS2
        {
            Vector3D(-0.5f, -0.5f, 0.0f),
            Vector3D(1.0f, 0.5f, 0.0f),
            Vector3D(0, 0, 1),
            Vector3D(1, 1, 1),
        },
    };
    m_vb = GraphicsEngine::get()->createVertexBuffer();
    UINT size_list = ARRAYSIZE(list);
    void *shader_byte_code = nullptr;
    size_t size_shader = 0;
    if (!GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader))
    {
        return;
    }
    m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
    m_vb->load(list, sizeof(vertex), size_list, shader_byte_code, size_shader);
    GraphicsEngine::get()->releaseCompiledShader();
    if (!GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader))
    {
        return;
    }
    m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
    GraphicsEngine::get()->releaseCompiledShader();

    constant cc;
    cc.m_time = 0;

    m_cb = GraphicsEngine::get()->createConstantBuffer();
    m_cb->load(&cc, sizeof(constant));
}

void AppWindow::onUpdate()
{
    RECT rc = this->getClientWindowRect();
    Window::onUpdate();
    GraphicsEngine::get()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.0, 0.0, 1.0, 1.0);
    GraphicsEngine::get()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    updateQuadPosition();

    GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
    GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);
    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
    GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);
    GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
    GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(m_vb->getSizeVertexList(), 0);
    m_swap_chain->present(true);
}

void AppWindow::updateQuadPosition()
{
    constant cc;
    cc.m_time = ::GetTickCount();

    cc.m_world.setTranslation(Vector3D(0, 0, 0));
    cc.m_view.setIdentity();
    RECT rc = this->getClientWindowRect();
    cc.m_proj.setOrthoLH((rc.right - rc.left) / 400, (rc.bottom - rc.top) / 400, -4, 4);
    m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &cc);
}

void AppWindow::onDestroy()
{
    Window::onDestroy();
    m_vb->release();
    m_swap_chain->release();
    m_vs->release();
    m_ps->release();
    GraphicsEngine::get()->release();
}

AppWindow::~AppWindow()
{
}