#pragma once
#include <memory>
#include "Vector3D.h"
class Matrix4x4
{
public:
    Matrix4x4() {}

    void setIdentity()
    {
        ::memset(m_mat, 0, sizeof(float));
        for (int i = 0; i < 4; i++)
            m_mat[i][i] = 1;
    }

    void setTranslation(const Vector3D &vector)
    {
        setIdentity();
        m_mat[3][0] = vector.m_x;
        m_mat[3][1] = vector.m_y;
        m_mat[3][2] = vector.m_z;
    }

    void setOrthoLH(float width, float height, float near_plane, float far_plane)
    {
        setIdentity();
        m_mat[0][0] = 2 / width;
        m_mat[1][1] = 2 / height;
        m_mat[2][2] = 1 / (far_plane - near_plane);
        m_mat[3][3] = -near_plane / (far_plane - near_plane);
    }

    ~Matrix4x4() {}
    float m_mat[4][4];
};