#pragma once

class Vector3D
{
public:
    float m_x, m_y, m_z = 0;
    Vector3D() {}
    Vector3D(float x, float y, float z) : m_x(x), m_y(y), m_z(z) {}
    Vector3D(const Vector3D &vector) : m_x(vector.m_x), m_y(vector.m_y), m_z(vector.m_z) {}
    ~Vector3D() {}
};