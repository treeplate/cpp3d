#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
class GraphicsEngine;
class DeviceContext;

class VertexShader
{
public:
    VertexShader();
    ~VertexShader();
    bool release();

private:
    friend class GraphicsEngine;
    friend class DeviceContext;
    ID3D11VertexShader *m_vs;
    bool init(const void *shader_byte_code, size_t byte_code_size);
};